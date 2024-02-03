#pragma once

#include <cstddef>

class Socket {
public:
    Socket();
    ~Socket();
    explicit operator int();

private:
    int _handle;

#ifdef AV_PLATFORM_WIN
    WSADATA _wsaData;
#endif
};