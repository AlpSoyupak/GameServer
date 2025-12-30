#pragma once
#include <cstdint>

struct Unit {
    uint32_t unit_id;
    uint32_t player_id;
    int32_t  x;
    int32_t  y;

    // Target for movement
    int32_t target_x;
    int32_t target_y;
    bool    is_moving = false;

    // Optional: other state (health, type, etc.)
};
