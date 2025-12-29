#include "map_generator.hpp"
#include <FastNoiseLite.h>
#include <iostream>

WorldMap MapGenerator::generate(uint32_t seed, float noiseScale, float threshold, float islandFallOff, int octaves) {
    WorldMap map;
    map.seed = seed;
    map.walkable.resize(MAP_WIDTH * MAP_HEIGHT);

    FastNoiseLite noise;
    noise.SetSeed((int)seed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(noiseScale);

    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(octaves);
    noise.SetFractalLacunarity(2.0f);
    noise.SetFractalGain(0.5f);

    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            float n = noise.GetNoise((float)x, (float)y);
            float n01 = (n + 1.0f) * 0.5f;

            float nx = (float)x / MAP_WIDTH  - 0.5f;
            float ny = (float)y / MAP_HEIGHT - 0.5f;
            float d  = std::sqrt(nx*nx + ny*ny) / 0.7071f;
            d = d * d * d; // Unity-like falloff

            float island = n01 - d * islandFallOff;

            map.walkable[y * MAP_WIDTH + x] = (island > threshold);
        }
    }

    int ones = 0;
    for (size_t i = 0; i < map.walkable.size(); ++i)
        ones += map.walkable[i];

    std::cout << "Walkable count: " << ones << " / "
            << map.walkable.size() << std::endl;

    return map;
}