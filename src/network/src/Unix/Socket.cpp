#include "Network/Socket.h"
#include "Common/Logging/Log.h"

#include <unistd.h>
#include <sys/socket.h>
#include <pcap/socket.h>

Socket::Socket() {
    _handle = socket(AF_INET, SOCK_STREAM, 0);
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
    if (result != 0) {
        LOG_WARN("network", "Failed to connect to server: {}", errno);
        Close();
        return false;
    }

    return true;
}

void Socket::Close() const {
    close(_handle);
    LOG_TRACE("network", "Socket closed");
}