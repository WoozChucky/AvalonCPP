#pragma once

#include <Common/Logging/Log.h>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/system/error_code.hpp>

namespace boostssl = boost::asio::ssl;

template<class Stream = boostssl::stream<boost::asio::ip::tcp::socket>>
class SslSocket
{
public:
    explicit SslSocket(boost::asio::ip::tcp::socket&& socket, boost::asio::ssl::context& sslContext) : _sslSocket(std::move(socket), sslContext)
    {
        _sslSocket.set_verify_mode(boostssl::verify_none);
    }

    // adapting tcp::socket api
    void close(boost::system::error_code& error)
    {
        _sslSocket.lowest_layer().close(error);
    }

    void shutdown(boost::asio::socket_base::shutdown_type what, boost::system::error_code& shutdownError)
    {
        _sslSocket.shutdown(shutdownError);
        _sslSocket.lowest_layer().shutdown(what, shutdownError);
    }

    template<typename MutableBufferSequence, typename ReadHandlerType>
    void async_read_some(MutableBufferSequence const& buffers, ReadHandlerType&& handler)
    {
        _sslSocket.async_read_some(buffers, std::move(handler));
    }

    template<typename ConstBufferSequence, typename WriteHandlerType>
    void async_write_some(ConstBufferSequence const& buffers, WriteHandlerType&& handler)
    {
        _sslSocket.async_write_some(buffers, std::move(handler));
    }

    template<typename ConstBufferSequence>
    std::size_t write_some(ConstBufferSequence const& buffers, boost::system::error_code& error)
    {
        return _sslSocket.write_some(buffers, error);
    }

    template<typename SettableSocketOption>
    void set_option(SettableSocketOption const& option, boost::system::error_code& error)
    {
        _sslSocket.lowest_layer().set_option(option, error);
    }

    boost::asio::ip::tcp::socket::endpoint_type remote_endpoint() const
    {
        return _sslSocket.lowest_layer().remote_endpoint();
    }

    // ssl api
    template<typename HandshakeHandlerType>
    void async_handshake(boostssl::stream_base::handshake_type type, HandshakeHandlerType&& handler)
    {
        _sslSocket.async_handshake(type, std::move(handler));
    }

protected:
    Stream _sslSocket;
};
