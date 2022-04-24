#include "chunk.h"

#include <cstddef>
#include <iostream>

#include <glad/glad.h>

#include <cpmath/act/act_mat4.h>

#include "../camera.h"
#include "light.h"

int last_chunk_id = -1;

Chunk NewChunk(float *noise, float pX, float pZ) {
    last_chunk_id++;

    Chunk chunk;
    chunk.id = last_chunk_id;

    //Vertices
    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_WIDTH; y++) {
            Vertex vert;

            vert.position = vec3_make(
                x,
                noise[(int)x + y * (int)CHUNK_WIDTH] * CHUNK_HEIGHT,
                y
            );
            vert.normal = vec3_make(0, 0, 0);
            vert.texcoord = vec2_make(
                (float)x / (float)CHUNK_WIDTH,
                (float)y / (float)CHUNK_WIDTH
            );

            chunk.vertices.push_back(vert);

            // TODO: CALCULATE THE NORMALS
        }
    }

    //Indices
    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_WIDTH; y++) {
            int index = x + y * CHUNK_WIDTH;

            if (x < CHUNK_WIDTH - 1 && y < CHUNK_WIDTH - 1) {
                chunk.indices.push_back(index);
                chunk.indices.push_back(index + 1);
                chunk.indices.push_back(index + CHUNK_WIDTH);

                chunk.indices.push_back(index + 1);
                chunk.indices.push_back(index + CHUNK_WIDTH + 1);
                chunk.indices.push_back(index + CHUNK_WIDTH);
            }
        }
    }

    //Normals
    for (int i = 0; i < chunk.indices.size(); i += 3) {
        vec3 v1 = chunk.vertices[chunk.indices[i + 1]].position;
        vec3 v2 = chunk.vertices[chunk.indices[i + 2]].position;
        vec3 v3 = chunk.vertices[chunk.indices[i]].position;

        vec3 normal = normalize(vec3_cross(
            vec3_sub(v2, v1),
            vec3_sub(v3, v1)
        ));

        chunk.vertices[chunk.indices[i]].normal = normal;
        chunk.vertices[chunk.indices[i + 1]].normal = normal;
        chunk.vertices[chunk.indices[i + 2]].normal = normal;
    }

    //Chunk position
    chunk.spawn_x = pX;
    chunk.spawn_z = pZ;

    chunk.model = mat4_identity();
    chunk.model = mat4_translate(chunk.model, 
        vec3_make(
            (float)chunk.spawn_x,
            0.0f,
            (float)chunk.spawn_z
        ));

    return chunk;
}

void MkBuffers(Chunk *chunk) {
    //Buffers
    glGenVertexArrays(1, &chunk->vao); //VAO
    glBindVertexArray(chunk->vao);

    glGenBuffers(1, &chunk->vbo); //VBO
    glGenBuffers(1, &chunk->ebo); //EBO
    glBindBuffer(GL_ARRAY_BUFFER, chunk->vbo);
    glBufferData(GL_ARRAY_BUFFER, chunk->vertices.size() * sizeof(Vertex), &chunk->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunk->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunk->indices.size() * sizeof(unsigned int), &chunk->indices[0], GL_STATIC_DRAW);

    // VERTICES (3)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    // NORMALS (3)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // TEXTURE COORDINATES (2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));

    glBindVertexArray(0);
}

void RenderChunk(const Chunk &chunk, Program p)
{
    glBindVertexArray(chunk.vao);

    // Bind the position of the chunk
    BindMat4(p, "model", chunk.model);

    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glDrawElements(GL_TRIANGLES, chunk.indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void ChunkDestroy(Chunk &chunk) {
    glDeleteVertexArrays(1, &chunk.vao);
    glDeleteBuffers(1, &chunk.vbo);
    glDeleteBuffers(1, &chunk.ebo);

    // Crear vertices and indices
    chunk.vertices.clear();
    chunk.indices.clear();

    chunk.trees.clear(); // Clear trees
}
