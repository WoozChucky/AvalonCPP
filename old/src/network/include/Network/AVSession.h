#pragma once

#include <Common/Logging/Log.h>
#include <Common/Utilities/Duration.h>
#include <Network/AVSocket.h>
#include <Network/SslSocket.h>
#include <boost/asio/ip/tcp.hpp>
#include <memory>

typedef std::function<void(bool)> ConnectResultCallback;
typedef std::function<void(MessageBuffer&)> MessageReceivedCallback;

class AVSession : public AVSocket<AVSession, SslSocket<>> {
    typedef AVSocket<AVSession, SslSocket<>> AvalonSocket;
public:

    explicit AVSession(boost::asio::ip::tcp::socket&& socket);
    ~AVSession();

    void SetConnectResultCallback(const ConnectResultCallback& callback);
    void SetMessageReceivedCallback(const MessageReceivedCallback& callback);

    void Start() override;
    bool Update() override;
    void ReadHandler() override;

private:
    void HandshakeHandler(boost::system::error_code const& error);

    ConnectResultCallback _connectCallback;
    MessageReceivedCallback _messageReceivedCallback;

};
