#ifndef __VEC2_H__
#define __VEC2_H__

#include <iostream>
#include <math.h>

struct vec2 {
    float x;
    float y;
};

inline bool vec2_is_zero(vec2 a) {
    return a.x == 0 && a.y == 0;
}

inline vec2 vec2_make(float x, float y) {
    vec2 result = {x, y};
    return result;
}

inline vec2 vec2_add(vec2 a, vec2 b) {
    vec2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

inline vec2 vec2_sub(vec2 a, vec2 b) {
    vec2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

inline vec2 vec2_multiply(vec2 a, vec2 b) {
    vec2 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    return result;
}

inline vec2 vec2_multiply(vec2 a, float b) {
    vec2 result;
    result.x = a.x * b;
    result.y = a.y * b;
    return result;
}

inline vec2 vec2_neg(vec2 a) {
    vec2 result;
    result.x = -a.x;
    result.y = -a.y;
    return result;
}

inline float vec2_dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

inline float vec2_length(vec2 a) {
    return sqrtf(vec2_dot(a, a));
}

inline float vec2_distance(vec2 a, vec2 b) {
    return vec2_length(vec2_sub(a, b));
}

// Get hash of vec2
namespace std {
    template<>
    struct hash<vec2> {
        size_t operator()(const vec2& v) const {
            return hash<float>()(v.x) ^ hash<float>()(v.y);
        }
    };
}

#endif
