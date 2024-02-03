//
// Created by nunol on 2/2/2024.
//
#include "NetworkDaemon.h"

#include <fmt/core.h>

#include "EncodingUtils.h"
#include "Common/Logging/Log.h"

#include <Proto/network-packet.pb.h>
#include <Proto/CRequestServerInfoPacket.pb.h>
#include <Proto/SServerInfoPacket.pb.h>

using namespace Avalon::Network::Packets::Abstractions;
using namespace Avalon::Network::Packets::Handshake;
using namespace Avalon::Common;

NetworkDaemon::NetworkDaemon() {
    client_ = std::make_unique<TLSClient>("127.0.0.1", 21000, [this](auto && PH1) { OnDataReceived(std::forward<decltype(PH1)>(PH1)); });
    cryptoSession_ =std::make_unique<Avalon::Crypto::CryptoSession>();
}

NetworkDaemon::~NetworkDaemon() {
    client_->SignalShutdown();
}

void NetworkDaemon::Start() {

    client_->ConnectAsync([this](bool success) { OnConnectionResult(success); });

    std::unique_lock<std::mutex> lock(mtx_);
    if (cv_.wait_for(lock, std::chrono::seconds(5), [this] { return isConnected_.load(); })) {
        // Now that we're connected, call RunAsync
        client_->RunAsync();
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

        client_->SendDataAsync(packetWithLength);
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

    LOG_TRACE("network", "Received packet of type {}", NetworkPacketTypeToString(receivedPacket.header().type()));

    switch (receivedPacket.header().type()) {
        case NetworkPacketType::SMSG_SERVER_INFO: {
            SServerInfoPacket packet;
            packet.ParseFromString(receivedPacket.payload());
            // Convert string const & to const vector<unsigned char> &

            auto convertedPublicKey = std::vector<unsigned char>(packet.publickey().begin(), packet.publickey().end());

            cryptoSession_->Initialize(std::move(convertedPublicKey));

            LOG_INFO("network", "Server version: {}", packet.serverversion());
            break;
        }
        default:
            LOG_WARN("network", "Unknown packet type");
            break;
    }

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


