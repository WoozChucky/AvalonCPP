//
// Created by nunol on 2/1/2024.
//

#ifndef TLSCLIENT_H
#define TLSCLIENT_H
#include <functional>
#include <string>
#include <memory>
#include <openssl/ssl.h>

#ifdef __WIN32__
#include <winsock2.h>
#else
#include <sys/socket.h>
#include "Network/Socket.h"

#endif

using TLSReadCallback = std::function<void(const std::vector<char>&)>;

class TLSClient {
public:
    TLSClient(std::string  serverAddress, int serverPort, TLSReadCallback readCallback);
    ~TLSClient();

    void ConnectAsync(const std::function<void(bool)>& callback = nullptr);
    void SignalShutdown();
    bool SendDataAsync(const std::string &data);
    void RunAsync();


private:
    std::string serverAddress_;
    int serverPort_;
    Socket* _socket;
    WSADATA wsaData_;
    SOCKET clientSocket_;
    sockaddr_in serverAddr_;

    std::unique_ptr<SSL, decltype(&::SSL_free)> ssl_;
    std::unique_ptr<SSL_CTX, decltype(&::SSL_CTX_free)> sslContext_;
    volatile bool shutdownRequested_ = false;
    volatile bool connected_ = false;

    TLSReadCallback readCallback_;


    bool LoadCertificate();
    bool SendData(const std::string& data);
    void Shutdown();
};



#endif //TLSCLIENT_H
