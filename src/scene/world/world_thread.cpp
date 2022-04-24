#include "world_thread.h"

#include <cpmath/cpmath.h>

#include <vector>
#include <thread>

#include "world.h"
#include "../camera.h"
#include "../../win/window.h"

vec3        camera_old_position = vec3_make(0, 0, 0);
const int   chunks_circle_radius = 7;
bool world_thread_running = true;

void GenerateChunks()
{
    Chunk currespondent_chunk = world->GetChunkFromCoords(camera_old_position.x, camera_old_position.z);

    // The chunks will spread around the player
    for (int x = -chunks_circle_radius; x < chunks_circle_radius; x++)
    {
        for (int z = -chunks_circle_radius; z < chunks_circle_radius; z++)
        {
            //The spawn position will be CHUNK_WIDTH aligned as a grid of chunks with 0 of padding (every chunk is touching the others)
            int spawn_x = currespondent_chunk.spawn_x + x * (CHUNK_WIDTH);
            int spawn_z = currespondent_chunk.spawn_z + z * (CHUNK_WIDTH);

            spawn_x = spawn_x - (spawn_x % (CHUNK_WIDTH));
            spawn_z = spawn_z - (spawn_z % (CHUNK_WIDTH));

            //Check if the chunk exists
            Chunk c = world->GetChunkFromCoords(spawn_x,
                                                spawn_z);

            // Check if the camera cords are in the chunk
            if(c.id != -1) {
                continue;
            }

            // Generate chunk
            world_mutex.lock();
            Chunk chunk = NewChunk(
                world->GetPartialHeightMap(
                    spawn_x,
                    spawn_z
                ),
                spawn_x,
                spawn_z
            );

            // In a chunk there can be 0 <= q <= 2 trees
            for (int q = 0; q < rand() % 3; q++)
            {
                // Coordinates of the tree
                int tree_x = spawn_x + rand() % CHUNK_WIDTH;
                int tree_z = spawn_z + rand() % CHUNK_WIDTH;
                int tree_y = world->GetPartialHeightMap(tree_x, tree_z)[0] * CHUNK_HEIGHT; // TODO: This is already in the chunk vertices, take the height from there

                // Generate tree
                Tree tree = NewTree(
                    vec3_make(
                        tree_x,
                        tree_y - 2, // The tree can not touch the ground, so we need to substract 1
                        tree_z
                    )
                );

                // Add tree to chunk
                chunk.trees.push_back(tree);
            }

            world->chunks_to_mk.push_back(chunk);

            world_mutex.unlock();
        }
    }
}

void ThreadedWorldGeneration()
{
    GenerateChunks();

    while (world_thread_running)
    {
        // Wait for the next frame
        camera_mutex.lock();
            vec3 cm_tmp = camera_position;
        camera_mutex.unlock();
        if (camera_old_position.x != cm_tmp.x || camera_old_position.z != cm_tmp.z)
        {
            // If moved           
            camera_old_position = cm_tmp;
            GenerateChunks();
        }
    }
}
