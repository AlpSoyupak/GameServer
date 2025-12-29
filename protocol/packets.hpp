#pragma once
#include <cstdint>

enum class PacketType : uint8_t {
    Join  = 1,
    Input = 2,
    State = 3,
    MapInit = 4
};

constexpr uint8_t PROTOCOL_VERSION = 1;

