#ifndef __ACT_MAT4_H__
#define __ACT_MAT4_H__

#include <math.h>

#include "act.h"

#include "../com/mat4.h"
#include "../com/vec3.h"

//fov is in radiants
inline mat4 mat4_perspective(float fov, float aspect, float near, float far) {
    mat4 result = mat4_identity();
    if (fov == 0.0f || aspect == 0.0f || near == 0.0f || far == 0.0f) {
        return result;
    }

    float halfFov = tanf(fov / 2.0f);
    float f = 1 / halfFov;
    float zRange = near - far;

    float A = (-far - near) / zRange;
    float B = (2.0f * far * near) / zRange;

    vec4 r0 = vec4_make(f/aspect, 0.0f,   0.0f, 0.0f);
    vec4 r1 = vec4_make(0.0f,     f,      0.0f, 0.0f);
    vec4 r2 = vec4_make(0.0f,     0.0f,   A,    B);
    vec4 r3 = vec4_make(0.0f,     0.0f,   1.0f, 0.0f);
    result = mat4_make(r0, r1, r2, r3);

    return result;
}

inline mat4 mat4_orthographic(float left, float right, float bottom, float top, float near, float far) {
    mat4 result = mat4_identity();
    if (left == right || bottom == top || near == far) {
        return result;
    }

    float width = right - left;
    float height = top - bottom;
    float depth = far - near;

    vec4 r0 = vec4_make(2.0f / width, 0.0f, 0.0f, -(right + left) / width);
    vec4 r1 = vec4_make(0.0f, 2.0f / height, 0.0f, -(top + bottom) / height);
    vec4 r2 = vec4_make(0.0f, 0.0f, -2.0f / depth, -(far + near) / depth);
    vec4 r3 = vec4_make(0.0f, 0.0f, 0.0f, 1.0f);
    result = mat4_make(r0, r1, r2, r3);

    return result;
}

inline mat4 mat4_translate(mat4 a, vec3 v) {
    mat4 result = mat4_identity();
    if (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f) {
        return result;
    }

    vec4 r0 = vec4_make(1.0f, 0.0f, 0.0f, v.x);
    vec4 r1 = vec4_make(0.0f, 1.0f, 0.0f, v.y);
    vec4 r2 = vec4_make(0.0f, 0.0f, 1.0f, v.z);
    vec4 r3 = vec4_make(0.0f, 0.0f, 0.0f, 1.0f);
    result = mat4_make(r0, r1, r2, r3);

    return mat4_mul(a, result);
}

inline mat4 mat4_rotate_x(mat4 a, float angle) {
    mat4 result = mat4_identity();
    if (angle == 0.0f) {
        return result;
    }

    float c = cosf(angle);
    float s = sinf(angle);

    vec4 r0 = vec4_make(1.0f, 0.0f, 0.0f, 0.0f);
    vec4 r1 = vec4_make(0.0f, c,   -s,  0.0f);
    vec4 r2 = vec4_make(0.0f, s,   c,   0.0f);
    vec4 r3 = vec4_make(0.0f, 0.0f, 0.0f, 1.0f);
    result = mat4_make(r0, r1, r2, r3);

    return mat4_mul(a, result);
}

inline mat4 mat4_rotate_y(mat4 a, float angle) {
    mat4 result = mat4_identity();
    if (angle == 0.0f) {
        return result;
    }

    float c = cosf(angle);
    float s = sinf(angle);

    vec4 r0 = vec4_make(c,   0.0f, s,   0.0f);
    vec4 r1 = vec4_make(0.0f, 1.0f, 0.0f, 0.0f);
    vec4 r2 = vec4_make(-s,  0.0f, c,   0.0f);
    vec4 r3 = vec4_make(0.0f, 0.0f, 0.0f, 1.0f);
    result = mat4_make(r0, r1, r2, r3);

    return mat4_mul(a, result);
}

inline mat4 mat4_rotate_z(mat4 a, float angle) {
    mat4 result = mat4_identity();
    if (angle == 0.0f) {
        return result;
    }

    float c = cosf(angle);
    float s = sinf(angle);

    vec4 r0 = vec4_make(c,   -s,  0.0f, 0.0f);
    vec4 r1 = vec4_make(s,   c,   0.0f, 0.0f);
    vec4 r2 = vec4_make(0.0f, 0.0f, 1.0f, 0.0f);
    vec4 r3 = vec4_make(0.0f, 0.0f, 0.0f, 1.0f);
    result = mat4_make(r0, r1, r2, r3);

    return mat4_mul(a, result);
}

inline mat4 mat4_rotate(mat4 a, float angle, vec3 b) {
    mat4 result = mat4_identity();
    if (angle == 0.0f || b.x == 0.0f && b.y == 0.0f && b.z == 0.0f) {
        return result;
    }

    float c = cosf(angle);
    float s = sinf(angle);
    float t = 1.0f - c;

    vec4 r0 = vec4_make(t * b.x * b.x + c, t * b.x * b.y - s * b.z, t * b.x * b.z + s * b.y, 0.0f);
    vec4 r1 = vec4_make(t * b.x * b.y + s * b.z, t * b.y * b.y + c,   t * b.y * b.z - s * b.x, 0.0f);
    vec4 r2 = vec4_make(t * b.x * b.z - s * b.y, t * b.y * b.z + s * b.x, t * b.z * b.z + c,   0.0f);
    vec4 r3 = vec4_make(0.0f, 0.0f, 0.0f, 1.0f);
    result = mat4_make(r0, r1, r2, r3);

    return mat4_mul(a, result);
}

inline mat4 mat4_look_at(vec3 eye, vec3 target, vec3 up) {
    vec3 f = normalize(vec3_sub(target, eye));
    vec3 s = normalize(vec3_cross(f, up));
    vec3 u = vec3_cross(s, f);

    mat4 result = mat4_identity();
    vec4 r0 = vec4_make(s.x, s.y, s.z, -vec3_dot(s, eye));
    vec4 r1 = vec4_make(u.x, u.y, u.z, -vec3_dot(u, eye));
    vec4 r2 = vec4_make(-f.x, -f.y, -f.z, vec3_dot(f, eye));
    vec4 r3 = vec4_make(0.0f, 0.0f, 0.0f, 1.0f);
    result = mat4_make(r0, r1, r2, r3);
    
    return result;
}

#endif
