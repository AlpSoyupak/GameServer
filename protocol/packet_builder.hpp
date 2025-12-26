#pragma once

#include <span>
#include <cstdint>
#include "buffer.hpp"
#include "serialize.hpp"
#include "packets.hpp"

inline ByteBuffer build_join_packet() {
    ByteBuffer buf;
    buf.reserve(2);

    write<uint8_t>(buf, static_cast<uint8_t>(PacketType::Join));
    write<uint8_t>(buf, PROTOCOL_VERSION);

    return buf;
}

inline ByteBuffer build_input_packet(
    uint32_t player_id,
    int16_t move_x,
    int16_t move_y
) {
    ByteBuffer buf;
    buf.reserve(10);

    write<uint8_t>(buf, static_cast<uint8_t>(PacketType::Input));
    write<uint8_t>(buf, PROTOCOL_VERSION);
    write<uint32_t>(buf, player_id);
    write<int16_t>(buf, move_x);
    write<int16_t>(buf, move_y);

    return buf;
}

struct PlayerState {
    uint32_t id;
    float x;
    float y;
};

inline ByteBuffer build_state_packet(
    uint32_t tick,
    std::span<const PlayerState> players
) {
    ByteBuffer buf;
    buf.reserve(8 + players.size() * 12);

    write<uint8_t>(buf, static_cast<uint8_t>(PacketType::State));
    write<uint8_t>(buf, PROTOCOL_VERSION);
    write<uint32_t>(buf, tick);
    write<uint16_t>(buf, static_cast<uint16_t>(players.size()));

    for (const auto& p : players) {
        write<uint32_t>(buf, p.id);
        write<float>(buf, p.x);
        write<float>(buf, p.y);
    }

    return buf;
}

