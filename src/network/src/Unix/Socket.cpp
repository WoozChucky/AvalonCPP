#include "Network/Socket.h"

#include <unistd.h>
#include <sys/socket.h>
#include <pcap/socket.h>

Socket::Socket() {
    _handle = socket(AF_INET, SOCK_STREAM, 0);
    if (_handle == INVALID_SOCKET) {
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverIP, &serverAddress.sin_addr) <= 0) {
        // Handle error
    }
}

Socket::~Socket() {

}

Socket::operator int() {
    return _handle;
}