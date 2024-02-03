//
// Created by nunol on 2/2/2024.
//

#ifndef AVALON_NETWORKDAEMON_H
#define AVALON_NETWORKDAEMON_H

#include <vector>
#include <condition_variable>
#include <mutex>
#include <atomic>

#include "TLSClient.h"
#include "Common/Utilities/RingBuffer.h"
#include <Common/Crypto/CryptoSession.h>
#include <Proto/network-packet.pb.h>

using namespace Avalon::Network::Packets::Abstractions;

class NetworkDaemon {

public:
    NetworkDaemon();
    ~NetworkDaemon();

    void RegisterHandlers();
    void Start();

private:

    using PacketHandler = std::function<void(const NetworkPacket&)>;

    void OnDataReceived(const std::vector<char>& buffer);
    void OnConnectionResult(bool connected);

    void RegisterPacketHandler(NetworkPacketType type, PacketHandler handler);

    std::unique_ptr<Avalon::Crypto::CryptoSession> _cryptoSession;
    std::unique_ptr<TLSClient> _tlsClient;
    std::condition_variable cv_;
    std::mutex mtx_;
    std::atomic<bool> isConnected_ = false;
    std::map<NetworkPacketType, PacketHandler> _packetHandlers;
    std::unique_ptr<RingBuffer<NetworkPacket>> _receivedPacketQueue;
    std::unique_ptr<RingBuffer<NetworkPacket>> _sendPacketQueue;

    void ProcessReceivedPackets();

    std::unique_ptr<std::thread> packetProcessingThread;
    std::atomic<bool> stopProcessing;

    /**
     * Packet handlers
     */
    void OnServerInfoPacket(const NetworkPacket& packet);
};


#endif //AVALON_NETWORKDAEMON_H
