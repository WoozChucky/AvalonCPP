#include "NetworkDaemon.h"

#include <fmt/core.h>

#include "EncodingUtils.h"
#include "Common/Logging/Log.h"

#include <Proto/CRequestServerInfoPacket.pb.h>
#include <Proto/CClientInfoPacket.pb.h>
#include <Proto/SServerInfoPacket.pb.h>
#include <Proto/SHandshakePacket.pb.h>
#include <Proto/CHandshakePacket.pb.h>
#include <Proto/SHandshakeResultPacket.pb.h>

#include <utility>
#include <boost/asio/connect.hpp>

using namespace Avalon::Network::Packets::Handshake;
using namespace Avalon::Common;

NetworkDaemon::NetworkDaemon() {
    _session = nullptr;
    _cryptoSession =std::make_unique<Avalon::Crypto::CryptoSession>();
    _receivedPacketQueue = std::make_unique<RingBuffer<NetworkPacket>>(100);
    _sendPacketQueue = std::make_unique<RingBuffer<NetworkPacket>>(100);
    stopProcessing = false;
}

NetworkDaemon::~NetworkDaemon() {
    stopProcessing = true;
    if (packetProcessingThread && packetProcessingThread->joinable()) {
        _receivedPacketQueue->StopDequeue();
        packetProcessingThread->join();
    }
    if (packetSendingThread && packetSendingThread->joinable()) {
        _sendPacketQueue->StopDequeue();
        packetSendingThread->join();
    }
}

void NetworkDaemon::Start(boost::asio::io_context &ioContext) {

    boost::asio::ip::tcp::socket socket(ioContext);
    boost::asio::ip::tcp::resolver resolver(ioContext);
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "21000");
    boost::asio::connect(socket, endpoints);

    _session = std::make_shared<AVSession>(std::move(socket));
    _session->SetConnectResultCallback([this](bool success) { OnConnectionResult(success); });
    _session->SetMessageReceivedCallback([this](MessageBuffer &buffer) { OnDataReceived(buffer); });
    _session->Start();

    std::unique_lock<std::mutex> lock(mtx_);
    if (cv_.wait_for(lock, std::chrono::seconds(5), [this] { return isConnected_.load(); })) {

        // Start the packet processing thread
        packetProcessingThread = std::make_unique<std::thread>(&NetworkDaemon::ProcessReceivedPackets, this);
        packetSendingThread = std::make_unique<std::thread>(&NetworkDaemon::ProcessSendPackets, this);

        CRequestServerInfoPacket payload;
        payload.set_clientversion(1000000);

        // Serialize the payload
        std::string payloadData;
        payload.SerializeToString(&payloadData);

        auto* header = new NetworkPacketHeader();
        header->set_version(0);
        header->set_type(NetworkPacketType::CMSG_SERVER_INFO);
        header->set_protocol(NetworkProtocol::Tcp);
        header->set_flags(NetworkPacketFlags::ClearText);

        NetworkPacket packet;
        packet.set_allocated_header(header);
        packet.set_payload(payloadData);

        std::string serializedPacket;
        packet.SerializeToString(&serializedPacket);

        // Prepend the length of the serialized packet
        int packetSize = serializedPacket.size();
        std::string encodedLength = Encoding::Base128(packetSize);
        std::string packetWithLength = encodedLength + serializedPacket;

        auto* buffer = new MessageBuffer(packetWithLength.length());
        buffer->Write(packetWithLength.c_str(), packetWithLength.length());
        _session->QueuePacket(std::move(*buffer));

    } else {
        fmt::print("NetworkDaemon failed to  start\n");
    }
}

std::string NetworkPacketTypeToString(NetworkPacketType type) {
    switch (type) {
        case ::UNKNOWN: return "UNKNOWN";
        case ::SMSG_SERVER_INFO: return "SMSG_SERVER_INFO";
        case ::SMSG_SERVER_HANDSHAKE: return "SMSG_SERVER_HANDSHAKE";
        case ::SMSG_SERVER_HANDSHAKE_RESULT: return "SMSG_SERVER_HANDSHAKE_RESULT";
            // Add all other cases here...
        default: return "UNKNOWN";
    }
}

void NetworkDaemon::OnDataReceived(MessageBuffer &messageBuffer) {

    NetworkPacket receivedPacket;

    auto convertedBuffer = std::vector<char>(messageBuffer.GetReadPointer(), messageBuffer.GetReadPointer() + messageBuffer.GetBufferSize());

    if (!Decoding::Packet(convertedBuffer, receivedPacket)) {
        LOG_WARN("network", "Failed to deserialize packet");
        return;
    }

    if (receivedPacket.header().type() == NetworkPacketType::UNKNOWN) {
        LOG_WARN("network", "Received packet of unknown type");
        return;
    }

    LOG_TRACE("network", "Received packet of type {}", NetworkPacketTypeToString(receivedPacket.header().type()));

    _receivedPacketQueue->Enqueue(receivedPacket);
}

void NetworkDaemon::OnConnectionResult(bool connected) {
    if (connected) {
        LOG_INFO("network", "Connected to server");

        isConnected_.store(true);
        cv_.notify_one();

    } else {
        LOG_INFO("network", "Failed to connect to server");
    }
}

void NetworkDaemon::RegisterHandlers() {
    RegisterPacketHandler(
            NetworkPacketType::SMSG_SERVER_INFO,
            [this](const NetworkPacket &packet) { OnServerInfoPacket(packet); }
    );
    RegisterPacketHandler(
            NetworkPacketType::SMSG_SERVER_HANDSHAKE,
            [this](const NetworkPacket &packet) { OnHandshakePacket(packet); }
    );
    RegisterPacketHandler(
            NetworkPacketType::SMSG_SERVER_HANDSHAKE_RESULT,
            [this](const NetworkPacket &packet) { OnHandshakeResultPacket(packet); }
    );
}

void NetworkDaemon::RegisterPacketHandler(NetworkPacketType type, NetworkDaemon::PacketHandler handler) {
    _packetHandlers[type] = std::move(handler);
}

void NetworkDaemon::ProcessReceivedPackets() {
    while (!stopProcessing) {
        auto optPacket = _receivedPacketQueue->Dequeue();
        if (!optPacket.has_value()) {
            LOG_TRACE("network", "Packet came empty");
            continue;
        }
        auto packet = optPacket.value();
        auto packetType = NetworkPacketTypeToString(packet.header().type());

        auto it = _packetHandlers.find(packet.header().type());
        if (it != _packetHandlers.end()) {

            auto start = std::chrono::high_resolution_clock::now();
            try {
                it->second(packet);
            } catch (const std::exception& e) {
                LOG_ERROR("network", "Error processing packet: {}", e.what());
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            LOG_TRACE("network", "Time spent processing packet {}: {}ms", packetType, elapsed.count());

        } else {
            LOG_WARN("network", "No handler for packet type {}", NetworkPacketTypeToString(packet.header().type()));
        }
    }
}

void NetworkDaemon::ProcessSendPackets() {
    while (!stopProcessing) {
        auto optPacket = _sendPacketQueue->Dequeue();
        if (!optPacket.has_value()) {
            LOG_TRACE("network", "Packet came empty");
            continue;
        }
        auto packet = optPacket.value();

        std::string serializedPacket;
        packet.SerializeToString(&serializedPacket);

        // Prepend the length of the serialized packet
        int packetSize = serializedPacket.size();
        std::string encodedLength = Encoding::Base128(packetSize);
        std::string packetWithLength = encodedLength + serializedPacket;

        auto* buffer = new MessageBuffer(packetWithLength.length());
        buffer->Write(packetWithLength.c_str(), packetWithLength.length());
        _session->QueuePacket(std::move(*buffer));
    }
}

/****************************************************
 ****************** Packet Handlers *****************
 ****************************************************/

void NetworkDaemon::OnServerInfoPacket(const NetworkPacket &packet) {
    SServerInfoPacket serverInfoPacket;
    serverInfoPacket.ParseFromString(packet.payload());
    LOG_INFO("network", "Server version: {}.{}.{}", serverInfoPacket.serverversion() / 10000, (serverInfoPacket.serverversion() / 100) % 100, serverInfoPacket.serverversion() % 100);

    const auto convertedPublicKey = std::vector<unsigned char>(serverInfoPacket.publickey().begin(), serverInfoPacket.publickey().end());
    if (!_cryptoSession->Initialize(convertedPublicKey))
    {
        LOG_ERROR("network", "Failed to initialize crypto session");
        return;
    }

    auto publicKeyBytes = _cryptoSession->GetPublicKeyBytes();

    CClientInfoPacket payload;
    payload.set_publickey(publicKeyBytes.data(), publicKeyBytes.size());

    // Serialize the payload
    std::string payloadData;
    payload.SerializeToString(&payloadData);

    auto* header = new NetworkPacketHeader();
    header->set_version(0);
    header->set_type(NetworkPacketType::CMSG_CLIENT_INFO);
    header->set_protocol(NetworkProtocol::Tcp);
    header->set_flags(NetworkPacketFlags::ClearText);

    NetworkPacket responsePacket;
    responsePacket.set_allocated_header(header);
    responsePacket.set_payload(payloadData);

    _sendPacketQueue->Enqueue(responsePacket);
}

void NetworkDaemon::OnHandshakePacket(const NetworkPacket &packet) {

    auto encryptedPayload = std::vector<U8>(packet.payload().begin(), packet.payload().end());

    auto decrypted = _cryptoSession->Decrypt(encryptedPayload);

    auto decryptedString = std::string(decrypted.begin(), decrypted.end());

    SHandshakePacket handshakePacket;
    handshakePacket.ParseFromString(decryptedString);

    CHandshakePacket payload;
    payload.set_handshakedata(handshakePacket.handshakedata());

    // Serialize the payload
    std::string cleartextPayloadData;
    payload.SerializeToString(&cleartextPayloadData);

    auto cleartextPayload = std::vector<U8>(cleartextPayloadData.begin(), cleartextPayloadData.end());

    auto encryptedResponsePayload = _cryptoSession->Encrypt(cleartextPayload);

    auto encryptedResponsePayloadString = std::string(encryptedResponsePayload.begin(), encryptedResponsePayload.end());

    auto* header = new NetworkPacketHeader();
    header->set_version(0);
    header->set_type(NetworkPacketType::CMSG_CLIENT_HANDSHAKE);
    header->set_protocol(NetworkProtocol::Tcp);
    header->set_flags(NetworkPacketFlags::Encrypted);

    NetworkPacket responsePacket;
    responsePacket.set_allocated_header(header);
    responsePacket.set_payload(encryptedResponsePayloadString);

    _sendPacketQueue->Enqueue(responsePacket);
}

void NetworkDaemon::OnHandshakeResultPacket(const NetworkPacket &packet) {

    auto encryptedPayload = std::vector<U8>(packet.payload().begin(), packet.payload().end());

    auto decrypted = _cryptoSession->Decrypt(encryptedPayload);

    auto decryptedString = std::string(decrypted.begin(), decrypted.end());

    SHandshakeResultPacket handshakeResultPacket;
    handshakeResultPacket.ParseFromString(decryptedString);

    LOG_INFO("network", "Server connection handshake result (Verified={})", handshakeResultPacket.verified());
}


