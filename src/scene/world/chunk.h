#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "../obj_3d.h"
#include "../../proc/shaders/shaders.h"

// Components
#include "components/tree.h"

#include <cpmath/cpmath.h>
#include <vector>

#define CHUNK_WIDTH     64
#define CHUNK_HEIGHT    32

struct Chunk {
    int id = -1;

    // ***********
    // Chunks spawn from 0, 0 in the world and spread around the player

    int spawn_x = 0;
    int spawn_z = 0;

    // ***********
    // Model matrix
    mat4 model;

    // ***********
    // Buffers

    unsigned int vao = -1;
    unsigned int vbo = -1;
    unsigned int ebo = -1;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    

    // *******************
    // Chunk components

    std::vector<Tree> trees;
};

// Noise is a 64x64 array of floats
Chunk   NewChunk(float *noise, float pX, float pZ);
void    MkBuffers(Chunk *chunk);
void    RenderChunk(const Chunk &chunk, Program p);
void    ChunkDestroy(Chunk &chunk);

#endif
