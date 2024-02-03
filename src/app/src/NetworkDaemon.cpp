//
// Created by nunol on 2/2/2024.
//
#include "NetworkDaemon.h"

#include <fmt/core.h>

#include "EncodingUtils.h"
#include "Common/Logging/Log.h"

#include <Proto/CRequestServerInfoPacket.pb.h>
#include <Proto/SServerInfoPacket.pb.h>

#include <utility>

using namespace Avalon::Network::Packets::Handshake;
using namespace Avalon::Common;

NetworkDaemon::NetworkDaemon() {
    _tlsClient = std::make_unique<TLSClient>("127.0.0.1", 21000, [this](auto && PH1) { OnDataReceived(std::forward<decltype(PH1)>(PH1)); });
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
    _tlsClient->SignalShutdown();
}

void NetworkDaemon::Start() {

    _tlsClient->ConnectAsync([this](bool success) { OnConnectionResult(success); });

    std::unique_lock<std::mutex> lock(mtx_);
    if (cv_.wait_for(lock, std::chrono::seconds(5), [this] { return isConnected_.load(); })) {

        // Start the packet processing thread
        packetProcessingThread = std::make_unique<std::thread>(&NetworkDaemon::ProcessReceivedPackets, this);

        // Now that we're connected, call RunAsync
        _tlsClient->RunAsync();
        //TODO: Send initial protocol message here

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

        //packet.Clear();

        _tlsClient->SendDataAsync(packetWithLength);
    } else {
        fmt::print("NetworkDaemon failed to  start\n");
    }
}

std::string NetworkPacketTypeToString(NetworkPacketType type) {
    switch (type) {
        case ::UNKNOWN: return "UNKNOWN";
        case ::SMSG_SERVER_INFO: return "SMSG_SERVER_INFO";
            // Add all other cases here...
        default: return "UNKNOWN";
    }
}

void NetworkDaemon::OnDataReceived(const std::vector<char> &buffer) {

    NetworkPacket receivedPacket;

    if (!Decoding::Packet(buffer, receivedPacket)) {
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
}

void NetworkDaemon::RegisterPacketHandler(NetworkPacketType type, NetworkDaemon::PacketHandler handler) {
    _packetHandlers[type] = std::move(handler);
}

/****************************************************
 ****************** Packet Handlers *****************
 ****************************************************/

void NetworkDaemon::OnServerInfoPacket(const NetworkPacket &packet) {
    SServerInfoPacket serverInfoPacket;
    serverInfoPacket.ParseFromString(packet.payload());
    LOG_INFO("network", "Server version: {}", serverInfoPacket.serverversion());

    const auto convertedPublicKey = std::vector<unsigned char>(serverInfoPacket.publickey().begin(), serverInfoPacket.publickey().end());
    _cryptoSession->Initialize(convertedPublicKey);
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





