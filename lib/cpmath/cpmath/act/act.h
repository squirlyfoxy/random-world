#ifndef __ACT_H__
#define __ACT_H__

#include <math.h>

#include "../com/vec2.h"
#include "../com/vec3.h"
#include "../com/vec4.h"

inline vec4 normalize(vec4 v) {
    float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    vec4 result = vec4_make(v.x / len, v.y / len, v.z / len, v.w / len);
    return result;
}

inline vec3 normalize(vec3 v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    vec3 result = vec3_make(v.x / length, v.y / length, v.z / length);
    return result;
}

inline vec2 normalize(vec2 v) {
    float length = sqrt(v.x * v.x + v.y * v.y);
    vec2 result = vec2_make(v.x / length, v.y / length);
    return result;
}

inline float angle(vec2 a, vec2 b) {
    float dot = a.x * b.x + a.y * b.y;
    float det = a.x * b.y - a.y * b.x;
    return atan2(det, dot) * 180 / M_PI;
}

#endif
