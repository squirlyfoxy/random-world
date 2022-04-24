#include "world.h"

#include <thread>
#include <iostream>

#include <glad/glad.h>

#include <cpmath/act/act_3d.h>

#include "world_thread.h"
#include "../camera.h"

#include "components/tree.h"

std::mutex world_mutex;

World::World() {
    mNoise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Perlin);

    // Shaders
    Shader vertexShader;
    vertexShader.source = world_vertex_shader;
    vertexShader.type = VERTEX_SHADER;

    Shader fragmentShader;
    fragmentShader.source =  world_fragment_shader;
    fragmentShader.type = FRAGMENT_SHADER;

    mShader.shaders.push_back(vertexShader);
    mShader.shaders.push_back(fragmentShader);

    NewProgram(&mShader);

    // ----
    // Binding not changable uniforms
    BindFloat(mShader, "ambientStrength", AMBIENT_STRETCH_FACTOR);
    BindFloat(mShader, "specularStrength", SPECULAR_STRETCH_FACTOR);
    BindVec4(mShader, "color", vec4_make(0.5f, 0.5f, 0.5f, 1.0f));
    
    // Basic light with materials
    BasicLight light;
    light.gPosition = vec3_make(0.0f, 0.0f, 0.0f);
    light.gColor = vec4_make(1, 1, 1, 1);
    light.gAmbient = vec3_make(0.2, 0.2, 0.2);
    light.gDiffuse = vec3_make(0.5, 0.5, 0.5);
    light.gSpecular = vec3_make(1, 1, 1);
    mChunkMaterial.can_reflect = false;
    mWoodMaterial.shininess = 4.0f;
    basic_lights.push_back(light);

    // Textures
    mWTexture.path = "assets/texture_grass.png";
    mWTextureSpecular.path = "assets/texture_grass_specular.png";
    mWoordTexture.path = "assets/wood.png";
    mWoordTextureSpecular.path = "assets/wood_specular.png";
    Texture_Load(&mWTexture);
    Texture_Load(&mWTextureSpecular);
    Texture_Load(&mWoordTexture);

    InitializeTree();

    //Start thread
    mWorldThread = std::thread(ThreadedWorldGeneration);
}

World::~World() {
    for (auto& chunk : chunks) {
        ChunkDestroy(chunk);
    }

    world_thread_running = false;
    mWorldThread.join();
}

float* World::GetPartialHeightMap(int x, int z) {
    float *heightMap = new float[(int)CHUNK_WIDTH * (int)CHUNK_WIDTH];

    //ES: If x = 0 and z = 0, take the first 64x64 chunk
    //ES: If x = 0 and z = 64, take the second 64x64 chunk
    //ES: If x = 64 and z = 0, take the third 64x64 chunk
    //ES: If x = 64 and z = 64, take the fourth 64x64 chunk ecc..

    /*
        -------------------
        |        |        |
        |   4    |   3    |
        |        |        |
        -------------------
        |        |        |
        |   1    |   2    |
        |        |        |
        -------------------
    */

    //Get everything from heights array

    for (int i = 0; i < CHUNK_WIDTH; i++) {
        for (int j = 0; j < CHUNK_WIDTH; j++) {
            heightMap[i + j * CHUNK_WIDTH] =
                mNoise.GetNoise(
                    (float)x + i,
                    (float)z + j
                );
        }
    }

    return heightMap;
}

Chunk World::GetChunkFromCoords(int x, int z) {
    Chunk chunk{};

    //Return the chunk that contains a point of coordinates x, z. Y is ignored
    world_mutex.lock();
        int cs_size = chunks.size();
    world_mutex.unlock();


    for (int i = 0; i < cs_size; i++) {
        // Check if the point is inside the [i] chunk (area, not coordinates)
        world_mutex.lock();
            if (
                x >= chunks[i].spawn_x &&
                x < chunks[i].spawn_x + CHUNK_WIDTH &&
                z >= chunks[i].spawn_z &&
                z < chunks[i].spawn_z + CHUNK_WIDTH
            ) {
                world_mutex.unlock();
                chunk = chunks[i];
                break;
            }

            // If the cords are not positive, check if the point is inside the [i] chunk (area, not coordinates)
            if (
                x <= chunks[i].spawn_x &&
                x > chunks[i].spawn_x - CHUNK_WIDTH &&
                z <= chunks[i].spawn_z &&
                z > chunks[i].spawn_z - CHUNK_WIDTH
            ) {
                world_mutex.unlock();
                chunk = chunks[i];
                break;
            }
        world_mutex.unlock();
    }
    return chunk;
}

void World::Render() {
    // Light binding
    basic_lights[0].gPosition = camera_position;

    for (int i = 0; i < basic_lights.size(); i++) {
        basic_lights[i].Bind(mShader, i);
    }
    // Sun
    BindVec3(mShader, "sun.direction", sun.gDirection);
    BindVec3(mShader, "sun.ambient", sun.gAmbient);
    BindVec3(mShader, "sun.diffuse", sun.gDiffuse);
    BindVec3(mShader, "sun.specular", sun.gSpecular);

    // Material of the chunk
    BindFloat(mShader, "material.shininess", mChunkMaterial.shininess);
    BindBool(mShader, "material.can_reflect", mChunkMaterial.can_reflect);

    //Camera
    camera_mutex.lock();
        BindMat4(mShader, "proj", camera_perspective_projection());
        BindMat4(mShader, "view", camera_view_matrix);
        BindVec3(mShader, "viewPos", camera_position);
    camera_mutex.unlock();

    world_mutex.lock();
        for (int x = 0; x < chunks_to_mk.size(); x++) {
            MkBuffers(&chunks_to_mk[x]);
            chunks.push_back(chunks_to_mk[x]);
            chunks_to_mk.erase(chunks_to_mk.begin() + x);
        }
        int chunk_size = chunks.size();
    world_mutex.unlock();

    glUseProgram(mShader.id); // Use shader

    for (int i = 0; i < chunk_size; i++) { //Render every chunk
        world_mutex.lock();

        //STAGE: RENDER DISTANCE
        //Distance between camera and chunk (pitagoras)
        camera_mutex.lock();
            vec3 c_pos = camera_position; //Camera position, tmp variable
        camera_mutex.unlock();

        float distance = sqrt(
            pow(
                (float)chunks[i].spawn_x - c_pos.x,
                2
            ) +
            pow(
                (float)chunks[i].spawn_z - c_pos.z,
                2
            )
        );

        //STAGE: RENDER THE CHUNK
        if (distance < 800 ) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mWTexture.id);

            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, mWTextureSpecular.id);

            // -----
            // We can render the chunk
            RenderChunk(chunks[i], mShader);

            // Trees
            BindTree();
            for (int x = 0; x < chunks[i].trees.size(); x++) {
                vec3 ch_pos = vec3_make(
                    chunks[i].trees[x].pos.x,
                    chunks[i].trees[x].pos.y,
                    chunks[i].trees[x].pos.z
                );
                bool is_camera_chunk = distance <= CHUNK_WIDTH;
                bool in_camera = is_object_in_camera_view(ch_pos, c_pos, DEG_TO_RAD(-yaw), camera_fov, 2.3f);
                if (!in_camera && !is_camera_chunk) {
                    continue;
                }

                distance = sqrt(
                    pow(
                        chunks[i].trees[x].pos.x - c_pos.x,
                        2
                    ) +
                    pow(
                        chunks[i].trees[x].pos.z - c_pos.z,
                        2
                    )
                );
                if (distance > 280) { // Render distance for trees
                    continue;
                }

                // -----
                // We can render the tree

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, mWoordTexture.id);

                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, mWoordTextureSpecular.id);

                BindFloat(mShader, "material.shininess", mWoodMaterial.shininess);
                BindBool(mShader, "material.can_reflect", mWoodMaterial.can_reflect);

                RenderTree(chunks[i].trees[x], mShader);
            }
            glBindVertexArray(0);
        } else { // Unload the chunk if out of render distance
            ChunkDestroy(chunks[i]); // Destory the buffers (chunk and trees)

            // Remove the chunk from the chunks vector
            chunks.erase(chunks.begin() + i);
        }

        //TODO: RENDER ONLY CHUNKS THAT ARE IN VIEW
        world_mutex.unlock();
    }
}
