//
// Created by nunol on 2/2/2024.
//

#ifndef AVALON_ENCODINGUTILS_H
#define AVALON_ENCODINGUTILS_H

#include <string>
#include <sstream>
#include <vector>

#include "proto/network-packet.pb.h"

using namespace Avalon::Network::Packets::Abstractions;

namespace Avalon::Common {
    namespace Encoding {
        std::string Base128(int value);
    }
    namespace Decoding {
        int Base128(const std::vector<char>& buffer, int& offset);
        bool Packet(const std::vector<char>& buffer, NetworkPacket& packet);
    }
}


std::string Avalon::Common::Encoding::Base128(int value) {
    std::ostringstream encoded;
    while (value >= 128) {
        encoded.put(static_cast<char>((value & 0x7F) | 0x80));
        value >>= 7;
    }
    encoded.put(static_cast<char>(value));
    return encoded.str();
}

int Avalon::Common::Decoding::Base128(const std::vector<char>& buffer, int& offset) {
    int result = 0;
    int shift = 0;
    char byte;

    do {
        byte = buffer[offset++];
        result |= (byte & 0x7F) << shift;
        shift += 7;
    } while (byte & 0x80);

    return result;
}

bool Avalon::Common::Decoding::Packet(const std::vector<char>& buffer, NetworkPacket& packet) {
    int offset = 0;

    // Decode the length of the serialized packet
    int packetSize = Base128(buffer, offset);

    // Check if the buffer contains enough data
    if (buffer.size() - offset < packetSize) {
        // Incomplete packet
        return false;
    }

    // Extract the serialized packet
    std::string serializedPacket(buffer.begin() + offset, buffer.begin() + offset + packetSize);

    // Parse the serialized packet
    if (!packet.ParseFromString(serializedPacket)) {
        // Parsing failed
        return false;
    }

    return true;
}

#endif //AVALON_ENCODINGUTILS_H
