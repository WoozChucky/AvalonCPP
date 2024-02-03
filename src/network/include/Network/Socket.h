#pragma once

#include <cstddef>

#ifdef AV_PLATFORM_WIN
#include <winsock2.h>
#endif

class Socket {
public:
    Socket();
    ~Socket();
    explicit operator int() const;

    bool Connect(const char* address, int port) const;
    void Close() const;

private:
    unsigned long long _handle = 0;

#ifdef AV_PLATFORM_WIN
    WSADATA _wsaData;
#endif
};
