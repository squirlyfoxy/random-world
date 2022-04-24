#ifndef __VEC4_H__
#define __VEC4_H__

#include <iostream>
#include <math.h>

struct vec4 {
    float x;
    float y;
    float z;
    float w;
};

inline bool vec4_is_zero(vec4 a) {
    return a.x == 0 && a.y == 0 && a.z == 0 && a.w == 0;
}

inline vec4 vec4_make(float x, float y, float z, float w) {
    vec4 result = {x, y, z, w};
    return result;
}

inline vec4 vec4_add(vec4 a, vec4 b) {
    vec4 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}

inline vec4 vec4_sub(vec4 a, vec4 b) {
    vec4 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}

inline vec4 vec4_multiply(vec4 a, vec4 b) {
    vec4 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    result.w = a.w * b.w;
    return result;
}

inline vec4 vec4_multiplty(vec4 a, float b) {
    vec4 result;
    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;
    return result;
}

inline vec4 vec4_neg(vec4 a) {
    vec4 result;
    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    result.w = -a.w;
    return result;
}

inline vec4 vec4_cross(vec4 a, vec4 b) {
    vec4 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    result.w = 0;
    return result;
}

inline float vec4_dot(vec4 a, vec4 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline float vec4_lenght(vec4 a) {
    return sqrtf(vec4_dot(a, a));
}

inline float vec4_distance(vec4 a, vec4 b) {
    return vec4_lenght(vec4_sub(a, b));
}

// Get hash of a vec4
namespace std {
    template <>
    struct hash<vec4> {
        size_t operator()(const vec4& v) const {
            return hash<float>()(v.x) ^ hash<float>()(v.y) ^ hash<float>()(v.z) ^ hash<float>()(v.w);
        }
    };
}

/*
    x, y, z and w are the red, green, blue and alpha values respectively.
    Returns the starting vector if the vector is zero.
*/
inline vec4 vec4_normalize_rgba(vec4 a) {
    if (vec4_is_zero(a)) {
        return a;
    }

    //Normalize vector
    vec4 result;
    result.x = a.x / 255.0f;
    result.y = a.y / 255.0f;
    result.z = a.z / 255.0f;
    result.w = a.w / 255.0f;
    return result;
}

#endif
