//
// Created by nunol on 2/2/2024.
//
#include "NetworkDaemon.h"

#include <fmt/core.h>

#include "EncodingUtils.h"

#include "proto/network-packet.pb.h"
#include "proto/CRequestServerInfoPacket.pb.h"
#include "proto/SServerInfoPacket.pb.h"

using namespace Avalon::Network::Packets::Abstractions;
using namespace Avalon::Network::Packets::Handshake;
using namespace Avalon::Common;

NetworkDaemon::NetworkDaemon() {
    client_ = std::make_unique<TLSClient>("127.0.0.1", 21000, [this](auto && PH1) { OnDataReceived(std::forward<decltype(PH1)>(PH1)); });
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

EC_KEY* GetPublicKeyFromBytes(const std::vector<unsigned char>& publicKeyBytes) {
    const unsigned char* p = publicKeyBytes.data();
    EC_KEY* publicKey = d2i_EC_PUBKEY(NULL, &p, publicKeyBytes.size());

    if (publicKey == NULL) {
        throw std::runtime_error("Invalid public key");
    }

    return publicKey;
}

void NetworkDaemon::OnDataReceived(const std::vector<char> &buffer) {

    NetworkPacket receivedPacket;

    if (!Decoding::Packet(buffer, receivedPacket)) {
        fmt::print("Failed to deserialize packet\n");
        return;
    }

    fmt::print("Received packet of type {}\n", NetworkPacketTypeToString(receivedPacket.header().type()));

    switch (receivedPacket.header().type()) {
        case NetworkPacketType::SMSG_SERVER_INFO: {
            SServerInfoPacket packet;
            packet.ParseFromString(receivedPacket.payload());
            packet.publickey();
            GetPublicKeyFromBytes(packet.publickey());
            fmt::print("Server version: {}\n", packet.serverversion());
            break;
        }
        default:
            fmt::print("Unknown packet type\n");
            break;
    }

}

void NetworkDaemon::OnConnectionResult(bool connected) {
    if (connected) {
        fmt::print("Connected to server\n");

        isConnected_.store(true);
        cv_.notify_one();

    } else {
        fmt::print("Failed to connect to server\n");
    }
}


