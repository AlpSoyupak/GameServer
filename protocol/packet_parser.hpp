#pragma once
#include "serialize.hpp"
#include "packets.hpp"

struct PacketHeader {
    PacketType type;
    uint8_t    version;
};

inline PacketHeader parse_header(ReadBuffer& buf) {
    PacketHeader h;
    h.type    = static_cast<PacketType>(read<uint8_t>(buf));
    h.version = read<uint8_t>(buf);
    return h;
}

struct InputPacket {
    uint32_t player_id;
    int16_t  dx;
    int16_t  dy;
};

inline InputPacket parse_input(ReadBuffer& buf) {
    InputPacket p;
    p.player_id = read<uint32_t>(buf);
    p.dx        = read<int16_t>(buf);
    p.dy        = read<int16_t>(buf);
    return p;
}

