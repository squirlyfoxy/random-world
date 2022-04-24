#ifndef __WORLD_H__
#define __WORLD_H__

#include "chunk.h"

#include "basic_light.h"
#include "directional_light.h"
#include "../../proc/texture.h"

#include <fast_noise.h>
#include <vector>

#include <semaphore>
#include <thread>
#include <mutex>

extern std::mutex world_mutex;

class World {
public:
    World();
    ~World();

    void Render();

    float* GetPartialHeightMap(int x, int z);
    // Check if in chunks exists one that contains the coords
    Chunk  GetChunkFromCoords(int x, int z);

    std::vector<Chunk> chunks;
    std::vector<Chunk> chunks_to_mk;

    // *********************
    // Components

    std::vector<BasicLight> basic_lights;
    DirectionalLight        sun;

    //Thread
    std::thread mWorldThread;
private:
    Texture mWTexture;
    Texture mWTextureSpecular;

    Texture mWoordTexture;
    Texture mWoordTextureSpecular;

    Material mChunkMaterial;
    Material mWoodMaterial;

    Program mShader;

    FastNoiseLite mNoise;
};

#endif
