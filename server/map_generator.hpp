#pragma once
#include "server_state.hpp"

class MapGenerator {
public:
    static WorldMap generate(
        uint32_t seed,
        float noiseScale = 0.05f,
        float threshold  = 0.45f,
        float islandFalloff = 0.9f,
        int octaves = 4
    );
};