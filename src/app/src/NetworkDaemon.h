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
#include <Common/Crypto/CryptoSession.h>

class NetworkDaemon {

public:
    NetworkDaemon();

    void Start();

private:

    void OnDataReceived(const std::vector<char>& buffer);
    void OnConnectionResult(bool connected);

    std::unique_ptr<Avalon::Crypto::CryptoSession> cryptoSession_;
    std::unique_ptr<TLSClient> client_;
    std::condition_variable cv_;
    std::mutex mtx_;
    std::atomic<bool> isConnected_ = false;
};


#endif //AVALON_NETWORKDAEMON_H
