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

size_t DecodeBase128(MessageBuffer& buffer) {
    size_t value = 0;
    int shift = 0;

    U8* initialPacketBuffer = buffer.GetBasePointer();
    size_t bufferSize = buffer.GetActiveSize();  // Assuming GetSize() is a function

    for (size_t i = 0; i < bufferSize; ++i) {
        U8 byte = initialPacketBuffer[i];
        value |= (byte & 0x7F) << shift;
        if ((byte & 0x80) == 0)
            break;
        shift += 7;
    }

    return value;
}

void AVSession::ReadHandler() {
    if (!IsOpen())
        return;

    // Decode the packet size from the start of the buffer
    size_t packet_size = DecodeBase128(GetReadBuffer());

    // Check if the buffer contains a complete packet
    if (GetReadBuffer().GetActiveSize() >= packet_size) {
        // Pass the complete packet to the callback function
        _messageReceivedCallback(GetReadBuffer());

        // Reset the read buffer
        GetReadBuffer().Reset();
    } else {
        LOG_ERROR("session", "Incomplete packet received");
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
