#pragma once
#include <optional>
#include <cstdint>
#include <vector>

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

struct ServerState {
    std::optional<WorldMap> map;
};