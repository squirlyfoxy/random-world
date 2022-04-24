#ifndef __VEC3_H__
#define __VEC3_H__

#include <iostream>
#include <math.h>

struct vec3 {
    float x;
    float y;
    float z;
};

inline bool vec3_is_zero(vec3 a) {
    return a.x == 0 && a.y == 0 && a.z == 0;
}

inline vec3 vec3_make(float x, float y, float z) {
    vec3 result = {x, y, z};
    return result;
}

inline vec3 vec3_add(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

inline vec3 vec3_sub(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

inline vec3 vec3_multiply(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    return result;
}

inline vec3 vec3_multiply(vec3 a, float b) {
    vec3 result;
    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    return result;
}

inline vec3 vec3_neg(vec3 a) {
    vec3 result;
    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    return result;
}

inline vec3 vec3_cross(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

inline float vec3_dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float vec3_length(vec3 a) {
    return sqrtf(vec3_dot(a, a));
}

inline float vec3_distance(vec3 a, vec3 b) {
    return vec3_length(vec3_sub(a, b));
}

// Gert the hash of a vec3
namespace std {
    template<>
    struct hash<vec3> {
        size_t operator()(const vec3& a) const {
            return hash<float>()(a.x) ^ hash<float>()(a.y) ^ hash<float>()(a.z);
        }
    };
}

#endif
