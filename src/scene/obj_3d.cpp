#include "obj_3d.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <unordered_map>
#include <iostream>
#include <string>

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            // position, normal and texcoord are used to calculate the hash
            // the hash is used to store the vertex in an unordered_map
            return ((hash<vec3>()(vertex.position) ^ (hash<vec3>()(vertex.normal) << 1)) >> 1) ^ (hash<vec2>()(vertex.texcoord) << 1);
        }
    };
}

bool operator==(const Vertex& a, const Vertex& b) {
    return (
        a.position.x == b.position.x &&
        a.position.y == b.position.y &&
        a.position.z == b.position.z
    ) && (
        a.normal.x == b.normal.x &&
        a.normal.y == b.normal.y &&
        a.normal.z == b.normal.z
    ) && (
        a.texcoord.x == b.texcoord.x &&
        a.texcoord.y == b.texcoord.y
    ); 
}

Object Read3DObject(const char *file)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs); 
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return Object();
    }

    Object object;
    object.vertices.reserve(scene->mMeshes[0]->mNumVertices);
    object.indices.reserve(scene->mMeshes[0]->mNumFaces * 3);

    // https://vulkan-tutorial.com/Loading_models
    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    const struct aiMesh* mesh = scene->mMeshes[0];

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const struct aiFace& face = mesh->mFaces[i];

        // Vertices
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            Vertex vertex;
            vertex.position = {
                mesh->mVertices[face.mIndices[j]].x,
                mesh->mVertices[face.mIndices[j]].y,
                mesh->mVertices[face.mIndices[j]].z
            };

            vertex.normal = {
                mesh->mNormals[face.mIndices[j]].x,
                mesh->mNormals[face.mIndices[j]].y,
                mesh->mNormals[face.mIndices[j]].z
            };

            vertex.texcoord = {
                mesh->mTextureCoords[0][face.mIndices[j]].x,
                mesh->mTextureCoords[0][face.mIndices[j]].y
            };

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(object.vertices.size());
                object.vertices.push_back(vertex);
            }

            object.indices.push_back(uniqueVertices[vertex]);
        }
    }

    std::cout << "Loaded " << scene->mMeshes[0]->mName.C_Str() << " with " << object.vertices.size() << " vertices and " << object.indices.size() << " indices." << std::endl;

    return object;
}

