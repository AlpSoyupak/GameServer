#pragma once

#include <span>
#include <cstdint>
#include "buffer.hpp"
#include "serialize.hpp"
#include "packets.hpp"
#include "server/server_state.hpp"

inline ByteBuffer build_join_packet() {
    ByteBuffer buf;
    buf.reserve(2);

    write<uint8_t>(buf, static_cast<uint8_t>(PacketType::Join));
    write<uint8_t>(buf, PROTOCOL_VERSION);

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

inline ByteBuffer build_map_init_packet(const WorldMap& map) {
    ByteBuffer buf;

    write<uint8_t>(buf, static_cast<uint8_t>(PacketType::MapInit));
    write<uint8_t>(buf, PROTOCOL_VERSION);

    write<uint32_t>(buf, map.width);
    write<uint32_t>(buf, map.height);
    write<uint32_t>(buf, map.seed);

    // Walkable bitmap
    for (uint8_t cell : map.walkable) {
        buf.push_back(std::byte{cell});
    }

    return buf;
}

inline ByteBuffer build_unit_update_packet(const Unit& unit) {
    ByteBuffer buf;

    // Packet type and protocol version
    write<uint8_t>(buf, static_cast<uint8_t>(PacketType::Command));
    write<uint8_t>(buf, PROTOCOL_VERSION);

    // Unit ID and owner
    write<uint32_t>(buf, unit.unit_id);
    write<uint32_t>(buf, unit.player_id);

    // Current position
    write<int32_t>(buf, unit.x);
    write<int32_t>(buf, unit.y);

    // Target position (where the unit is moving toward)
    write<int32_t>(buf, unit.target_x);
    write<int32_t>(buf, unit.target_y);

    // Moving state (1 = moving, 0 = idle)
    write<uint8_t>(buf, unit.is_moving ? 1 : 0);

    // Optional: add more fields here (health, type, etc.)

    return buf;
}

