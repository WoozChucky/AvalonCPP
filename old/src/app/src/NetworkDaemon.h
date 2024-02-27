//
// Created by nunol on 2/2/2024.
//

#ifndef AVALON_NETWORKDAEMON_H
#define AVALON_NETWORKDAEMON_H

#include <vector>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <thread>

#include "Common/Utilities/RingBuffer.h"
#include "Network/AVSession.h"
#include <Common/Crypto/CryptoSession.h>
#include <Proto/network-packet.pb.h>

using namespace Avalon::Network::Packets::Abstractions;

class NetworkDaemon {

public:
    NetworkDaemon();
    ~NetworkDaemon();

    void RegisterHandlers();
    void Start(boost::asio::io_context &ioContext);

    void Login(const std::string& username, const std::string& password);
    void SendAudioPacket(const std::vector<U8>& audioData);

    bool IsConnected() const;
    bool IsLogged() const;

private:

    using PacketHandler = std::function<void(const NetworkPacket&)>;

    void OnDataReceived(MessageBuffer &messageBuffer);
    void OnConnectionResult(bool connected);

    void RegisterPacketHandler(NetworkPacketType type, PacketHandler handler);

    std::unique_ptr<Avalon::Crypto::CryptoSession> _cryptoSession;
    std::shared_ptr<AVSession> _session;
    std::condition_variable cv_;
    std::mutex mtx_;
    std::atomic<bool> isConnected_ = false;
    std::atomic<bool> _isLogged = false;
    std::map<NetworkPacketType, PacketHandler> _packetHandlers;
    std::unique_ptr<RingBuffer<NetworkPacket>> _receivedPacketQueue;
    std::unique_ptr<RingBuffer<NetworkPacket>> _sendPacketQueue;

    void ProcessReceivedPackets();
    void ProcessSendPackets();

    void SendPacket(NetworkPacketType type, NetworkPacketFlags flags, google::protobuf::Message& message);

    std::unique_ptr<std::thread> packetProcessingThread;
    std::unique_ptr<std::thread> packetSendingThread;
    std::atomic<bool> stopProcessing{};

    /**
     * Packet handlers
     */
    void OnServerInfoPacket(const NetworkPacket& packet);
    void OnHandshakePacket(const NetworkPacket& packet);
    void OnHandshakeResultPacket(const NetworkPacket& packet);
    void OnAudioPacketReceived(const NetworkPacket& packet);
    void OnPingPacketReceived(const NetworkPacket &packet);
};


#endif //AVALON_NETWORKDAEMON_H
