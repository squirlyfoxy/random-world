#ifndef __OBJ_3D_H__
#define __OBJ_3D_H__

#include <vector>

#include <cpmath/cpmath.h>

struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 texcoord;
};

struct Object {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

Object Read3DObject(const char *file);
Object Read3DObject(void* data);

#endif
