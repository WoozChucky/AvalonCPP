#include <Network/Socket.h>

#include <Common/Debugging/Errors.h>

#include <iostream>
#include <string>
#include <vector>
#include <WS2tcpip.h>
#include "Common/Logging/Log.h"


Socket::Socket() {

    if (WSAStartup(MAKEWORD(2, 2), &_wsaData)) {
        throw std::runtime_error("Failed to initialize Winsock:" + std::to_string(WSAGetLastError()));
    }
    _handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_handle == INVALID_SOCKET) {
        throw std::runtime_error("Failed to create socket");
    }
}

Socket::~Socket() {

}


Socket::operator int() const {
    if (_handle > INT_MAX) {
        throw std::runtime_error("Socket handle is too large to be cast to int");
    }
    return (int)_handle;
}

bool Socket::Connect(const char *address, int port) const {

    // Resolve server address
    sockaddr_in serverAddr_{};
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_port = htons(port);
    serverAddr_.sin_addr.s_addr = inet_addr(address);

    int result = connect(_handle, reinterpret_cast<struct sockaddr*>(&serverAddr_), sizeof(serverAddr_));
    if (result == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK) {
        std::cerr << "Failed to connect to server: " << WSAGetLastError() << std::endl;
        Close();
        return false;
    }

    return true;
}

void Socket::Close() const {
    closesocket(_handle);
    WSACleanup();
    LOG_TRACE("network", "Socket closed");
}


