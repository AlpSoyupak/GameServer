#pragma once
#include "serialize.hpp"
#include "packets.hpp"

struct PacketHeader {
    PacketType type;
    uint8_t    version;
};

inline PacketHeader parse_header(ReadBuffer& buf) {
    PacketHeader h;
    h.version = read<uint8_t>(buf);
    h.type    = static_cast<PacketType>(read<uint8_t>(buf));
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

struct CommandPacket {
    uint8_t  type;
    uint32_t player_id;
    uint32_t unit_id;
    int32_t  target_x;
    int32_t  target_y;
    uint32_t target_unit_id;
};

inline CommandPacket parse_command(ReadBuffer& buf) {
    CommandPacket cmd;
    //cmd.type           = read<uint8_t>(buf);
    cmd.player_id      = read<uint32_t>(buf);
    cmd.unit_id        = read<uint32_t>(buf);
    cmd.target_x       = read<uint32_t>(buf);
    cmd.target_y       = read<uint32_t>(buf);
    cmd.target_unit_id = read<uint32_t>(buf);
    return cmd;
}