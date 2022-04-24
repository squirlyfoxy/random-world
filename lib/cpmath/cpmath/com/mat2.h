#ifndef __MAT2_H__
#define __MAT2_H__

#include "vec2.h"

struct mat2 {
    float m[2][2];
};

inline mat2 mat2_make(vec2 a, vec2 b) {
    mat2 result;
    result.m[0][0] = a.x;
    result.m[0][1] = a.y;
    result.m[1][0] = b.x;
    result.m[1][1] = b.y;
    return result;
}

inline mat2 mat2_identity() {
    mat2 result;
    result.m[0][0] = 1;
    result.m[0][1] = 0;
    result.m[1][0] = 0;
    result.m[1][1] = 1;
    return result;
}

inline mat2 mat2_zero() {
    mat2 result;
    result.m[0][0] = 0;
    result.m[0][1] = 0;
    result.m[1][0] = 0;
    result.m[1][1] = 0;
    return result;
}

inline mat2 mat2_inverse(mat2 m) {
    mat2 result;
    float det = m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];
    if (det == 0) {
        return mat2_zero();
    }

    result.m[0][0] = m.m[1][1] / det;
    result.m[0][1] = -m.m[0][1] / det;
    result.m[1][0] = -m.m[1][0] / det;
    result.m[1][1] = m.m[0][0] / det;
    return result;
}

inline mat2 mat2_scalr(mat2 m, float s) {
    mat2 result;
    result.m[0][0] = m.m[0][0] * s;
    result.m[0][1] = m.m[0][1] * s;
    result.m[1][0] = m.m[1][0] * s;
    result.m[1][1] = m.m[1][1] * s;
    return result;
}

inline mat2 mat2_mul(mat2 a, mat2 b) {
    mat2 result;
    result.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0];
    result.m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1];
    result.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0];
    result.m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1];
    return result;
}

#endif
