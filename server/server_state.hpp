#pragma once
#include "unit.hpp"
#include <optional>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <boost/asio.hpp>

constexpr int MAP_WIDTH  = 200;
constexpr int MAP_HEIGHT = 200;

struct WorldMap {
    uint32_t seed;
    uint32_t width  = MAP_WIDTH;
    uint32_t height = MAP_HEIGHT;

    // 1 byte per tile: 0 = water, 1 = land
    std::vector<uint8_t> walkable;

    bool is_walkable(int x, int y) const {
        return walkable[y * width + x] != 0;
    }
};

struct ClientInfo {
    boost::asio::ip::udp::endpoint endpoint;
    uint32_t player_id;
    // Optionally: last heartbeat timestamp, etc.
};

struct ServerState {
    std::optional<WorldMap> map;
    std::unordered_map<uint32_t, Unit> units;
    std::vector<ClientInfo> clients;
};