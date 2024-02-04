#pragma once

#include <Common/Logging/Log.h>
#include <Common/Utilities/MessageBuffer.h>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <atomic>
#include <queue>
#include <type_traits>

#define READ_BLOCK_SIZE 4096
#ifdef BOOST_ASIO_HAS_IOCP
#define SOCKET_USE_IOCP
#endif

/**
 * @class AVSocket
 *
 * Base async socket implementation
 *
 * @tparam T derived class type (CRTP)
 * @tparam Stream stream type used for operations on socket
 */
template<class T, class Stream = boost::asio::ip::tcp::socket>
class AVSocket : public std::enable_shared_from_this<T>
{
public:
    template<typename... Args>
    explicit AVSocket(boost::asio::ip::tcp::socket&& socket, Args&&... args) : _socket(std::move(socket), std::forward<Args>(args)...),
    _remoteAddress(_socket.remote_endpoint().address()), _remotePort(_socket.remote_endpoint().port()),
    _closed(false), _closing(false), _isWritingAsync(false)
    {
        _readBuffer.Resize(READ_BLOCK_SIZE);
    }

    AVSocket(AVSocket const& other) = delete;
    AVSocket(AVSocket&& other) = delete;
    AVSocket& operator=(AVSocket const& other) = delete;
    AVSocket& operator=(AVSocket&& other) = delete;

    virtual ~AVSocket()
    {
        _closed = true;
        boost::system::error_code error;
        _socket.close(error);
    }

    virtual void Start() = 0;

    virtual bool Update()
    {
        if (_closed)
            return false;

#ifndef SOCKET_USE_IOCP
        if (_isWritingAsync || (_writeQueue.empty() && !_closing))
            return true;

        for (; HandleQueue();)
            ;
#endif

        return true;
    }

    boost::asio::ip::address GetRemoteIpAddress() const
    {
        return _remoteAddress;
    }

    U16 GetRemotePort() const
    {
        return _remotePort;
    }

    void AsyncRead()
    {
        if (!IsOpen())
            return;

        _readBuffer.Normalize();
        _readBuffer.EnsureFreeSpace();
        _socket.async_read_some(boost::asio::buffer(_readBuffer.GetWritePointer(), _readBuffer.GetRemainingSpace()),
                                [self = this->shared_from_this()](boost::system::error_code const& error, size_t transferredBytes)
                                {
                                    self->ReadHandlerInternal(error, transferredBytes);
                                });
    }

    void AsyncReadWithCallback(void (T::*callback)(boost::system::error_code const&, std::size_t))
    {
        if (!IsOpen())
            return;

        _readBuffer.Normalize();
        _readBuffer.EnsureFreeSpace();
        _socket.async_read_some(boost::asio::buffer(_readBuffer.GetWritePointer(), _readBuffer.GetRemainingSpace()),
                                [self = this->shared_from_this(), callback](boost::system::error_code const& error, size_t transferredBytes)
                                {
                                    (self.get()->*callback)(error, transferredBytes);
                                });
    }

    void QueuePacket(MessageBuffer&& buffer)
    {
        _writeQueue.push(std::move(buffer));

        AsyncProcessQueue();
    }

    bool IsOpen() const { return !_closed && !_closing; }

    void CloseSocket()
    {
        if (_closed.exchange(true))
            return;

        boost::system::error_code shutdownError;
        _socket.shutdown(boost::asio::socket_base::shutdown_send, shutdownError);
        if (shutdownError)
            LOG_DEBUG("network", "Socket::CloseSocket: {} errored when shutting down socket: {} ({})", GetRemoteIpAddress().to_string(),
                         shutdownError.value(), shutdownError.message());

        OnClose();
    }

    void DelayedCloseSocket() { _closing = true; }

    MessageBuffer& GetReadBuffer() { return _readBuffer; }

protected:
    virtual void OnClose() { }

    virtual void ReadHandler() = 0;

    bool AsyncProcessQueue()
    {
        if (_isWritingAsync)
            return false;

        _isWritingAsync = true;

#ifdef SOCKET_USE_IOCP
        MessageBuffer& buffer = _writeQueue.front();
        _socket.async_write_some(boost::asio::buffer(buffer.GetReadPointer(), buffer.GetActiveSize()),
            [self = this->shared_from_this()](boost::system::error_code const& error, std::size_t transferedBytes)
            {
                self->WriteHandler(error, transferedBytes);
            });
#else
        _socket.async_write_some(boost::asio::null_buffers(),
                                 [self = this->shared_from_this()](boost::system::error_code const& error, std::size_t transferedBytes)
                                 {
                                     self->WriteHandlerWrapper(error, transferedBytes);
                                 });
#endif

        return false;
    }

    void SetNoDelay(bool enable)
    {
        boost::system::error_code err;
        _socket.set_option(boost::asio::ip::tcp::no_delay(enable), err);
        if (err)
            LOG_DEBUG("network", "Socket::SetNoDelay: failed to set_option(boost::asio::ip::tcp::no_delay) for {} - {} ({})",
                         GetRemoteIpAddress().to_string(), err.value(), err.message());
    }

    Stream& underlying_stream()
    {
        return _socket;
    }

private:
    void ReadHandlerInternal(boost::system::error_code const& error, size_t transferredBytes)
    {
        if (error)
        {
            CloseSocket();
            return;
        }

        LOG_TRACE("network", "Socket::ReadHandler: {} bytes read from {}:{}", transferredBytes, GetRemoteIpAddress().to_string(), GetRemotePort());

        _readBuffer.WriteCompleted(transferredBytes);
        ReadHandler();
    }

#ifdef SOCKET_USE_IOCP

    void WriteHandler(boost::system::error_code const& error, std::size_t transferedBytes)
    {
        if (!error)
        {
            LOG_TRACE("network", "Socket::WriteHandler: {} bytes written to {}:{}", transferedBytes, GetRemoteIpAddress().to_string(), GetRemotePort());
            _isWritingAsync = false;
            _writeQueue.front().ReadCompleted(transferedBytes);
            if (!_writeQueue.front().GetActiveSize())
                _writeQueue.pop();

            if (!_writeQueue.empty())
                AsyncProcessQueue();
            else if (_closing)
                CloseSocket();
        }
        else
            CloseSocket();
    }

#else

    void WriteHandlerWrapper(boost::system::error_code const& /*error*/, std::size_t /*transferedBytes*/)
    {
        _isWritingAsync = false;
        HandleQueue();
    }

    bool HandleQueue()
    {
        if (_writeQueue.empty())
            return false;

        MessageBuffer& queuedMessage = _writeQueue.front();

        std::size_t bytesToSend = queuedMessage.GetActiveSize();

        boost::system::error_code error;
        std::size_t bytesSent = _socket.write_some(boost::asio::buffer(queuedMessage.GetReadPointer(), bytesToSend), error);

        if (error)
        {
            if (error == boost::asio::error::would_block || error == boost::asio::error::try_again)
                return AsyncProcessQueue();

            _writeQueue.pop();
            if (_closing && _writeQueue.empty())
                CloseSocket();
            return false;
        }
        else if (bytesSent == 0)
        {
            _writeQueue.pop();
            if (_closing && _writeQueue.empty())
                CloseSocket();
            return false;
        }
        else if (bytesSent < bytesToSend) // now n > 0
        {
            queuedMessage.ReadCompleted(bytesSent);
            return AsyncProcessQueue();
        }

        _writeQueue.pop();
        if (_closing && _writeQueue.empty())
            CloseSocket();
        return !_writeQueue.empty();
    }

#endif

    Stream _socket;

    boost::asio::ip::address _remoteAddress;
    U16 _remotePort;

    MessageBuffer _readBuffer;
    std::queue<MessageBuffer> _writeQueue;

    std::atomic<bool> _closed;
    std::atomic<bool> _closing;

    bool _isWritingAsync;

};
