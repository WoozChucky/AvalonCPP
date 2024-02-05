#include <Network/AVSession.h>
#include <Network/SslContext.h>


AVSession::AVSession(boost::asio::ip::tcp::socket&& socket)
    : AvalonSocket(std::move(socket), SslContext::Instance()) { }

AVSession::~AVSession() = default;

void AVSession::SetConnectResultCallback(const ConnectResultCallback& callback) {
    _connectCallback = callback;
}
void AVSession::SetMessageReceivedCallback(const MessageReceivedCallback& callback) {
    _messageReceivedCallback = callback;
}

void AVSession::Start() {

    if (_connectCallback == nullptr) {
        LOG_ERROR("session", "ConnectResultCallback is not set");
        return;
    }

    if (_messageReceivedCallback == nullptr) {
        LOG_ERROR("session", "MessageReceivedCallback is not set");
        return;
    }

    underlying_stream().async_handshake(boost::asio::ssl::stream_base::client,
        [self = shared_from_this()](boost::system::error_code const& error) {

        self->HandshakeHandler(error);
    });
}

bool AVSession::Update() {
    return AVSocket::Update();
}

void AVSession::ReadHandler() {
    if (!IsOpen())
        return;

    //TODO: Here we have to get the read buffer and check if it's a complete packet
    //      we do that by getting the packet size that is encoded in base128 in the start of the packet

    {
        // Previous implementation here is wrong
        _messageReceivedCallback(GetReadBuffer());

        GetReadBuffer().Reset();
    }


    AsyncRead();
}

void AVSession::HandshakeHandler(const boost::system::error_code &error) {

    if (error)
    {
        LOG_ERROR("session", "SSL Handshake failed {}", error.message());
        CloseSocket();
        _connectCallback(false);
        return;
    }

    this->SetNoDelay(true);

    _connectCallback(true);

    AsyncRead();
}
