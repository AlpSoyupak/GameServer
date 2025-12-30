#pragma once
#include <cstdint>

enum class PacketType : uint8_t {
    Join  = 1,
    Command = 6,
    State = 3,
    MapInit = 4
};

constexpr uint8_t PROTOCOL_VERSION = 1;

