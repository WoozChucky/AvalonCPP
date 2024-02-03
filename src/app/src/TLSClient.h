#pragma once

#include <functional>
#include <string>
#include <memory>
#include <openssl/ssl.h>
#include <Network/Socket.h>

using TLSReadCallback = std::function<void(const std::vector<char>&)>;

class TLSClient {
public:
    TLSClient(std::string  serverAddress, int serverPort, TLSReadCallback readCallback);
    ~TLSClient();

    void ConnectAsync(const std::function<void(bool)>& callback);
    void SendDataAsync(const std::string &data, const std::function<void(bool)>& callback = nullptr);
    void SignalShutdown();

    void RunAsync();


private:
    std::string serverAddress_;
    int serverPort_;
    Socket* _socket;
    SSL* _ssl;
    SSL_CTX* _sslContext;

    volatile bool shutdownRequested_ = false;
    volatile bool connected_ = false;

    TLSReadCallback readCallback_;

    bool Connect();

    bool LoadCertificate();
    bool SendData(const std::string& data);
    void Shutdown();
};
