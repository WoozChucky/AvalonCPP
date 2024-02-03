#include <Network/Socket.h>

#include <iostream>
#include <string>
#include <vector>


Socket::Socket() {
    _handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_handle == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGet
}

Socket::~Socket() {

}

Socket::operator int() {
    return _handle;
}
