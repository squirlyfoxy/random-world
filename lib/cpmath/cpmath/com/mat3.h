#ifndef __MAT3_H__
#define __MAT3_H__

#include "vec3.h"

struct mat3 {
    float m[3][3];
};

inline mat3 mat3_make(vec3 a, vec3 b, vec3 c) {
    mat3 result;
    result.m[0][0] = a.x;
    result.m[0][1] = a.y;
    result.m[0][2] = a.z;
    result.m[1][0] = b.x;
    result.m[1][1] = b.y;
    result.m[1][2] = b.z;
    result.m[2][0] = c.x;
    result.m[2][1] = c.y;
    result.m[2][2] = c.z;
    return result;
}

inline mat3 mat3_identity() {
    mat3 result;
    result.m[0][0] = 1;
    result.m[0][1] = 0;
    result.m[0][2] = 0;
    result.m[1][0] = 0;
    result.m[1][1] = 1;
    result.m[1][2] = 0;
    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = 1;
    return result;
}

inline mat3 mat3_zero() {
    mat3 result;
    result.m[0][0] = 0;
    result.m[0][1] = 0;
    result.m[0][2] = 0;
    result.m[1][0] = 0;
    result.m[1][1] = 0;
    result.m[1][2] = 0;
    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = 0;
    return result;
}

inline mat3 mat2_inverse(mat3 m) {
    mat3 result;
    float det = m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[2][1] * m.m[1][2]) -
                m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[2][0] * m.m[1][2]) +
                m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[2][0] * m.m[1][1]);
    if (det == 0) {
        return mat3_zero();
    }

    result.m[0][0] = (m.m[1][1] * m.m[2][2] - m.m[2][1] * m.m[1][2]) / det;
    result.m[0][1] = (m.m[0][2] * m.m[2][1] - m.m[0][1] * m.m[2][2]) / det;
    result.m[0][2] = (m.m[0][1] * m.m[1][2] - m.m[0][2] * m.m[1][1]) / det;
    result.m[1][0] = (m.m[1][2] * m.m[2][0] - m.m[1][0] * m.m[2][2]) / det;
    result.m[1][1] = (m.m[0][0] * m.m[2][2] - m.m[0][2] * m.m[2][0]) / det;
    result.m[1][2] = (m.m[1][0] * m.m[0][2] - m.m[0][0] * m.m[1][2]) / det;
    result.m[2][0] = (m.m[1][0] * m.m[2][1] - m.m[2][0] * m.m[1][1]) / det;
    result.m[2][1] = (m.m[2][0] * m.m[0][1] - m.m[0][0] * m.m[2][1]) / det;
    result.m[2][2] = (m.m[0][0] * m.m[1][1] - m.m[1][0] * m.m[0][1]) / det;
    return result;
}

inline mat3 mat3_scalr(mat3 a, float b) {
    mat3 result;
    result.m[0][0] = a.m[0][0] * b;
    result.m[0][1] = a.m[0][1] * b;
    result.m[0][2] = a.m[0][2] * b;
    result.m[1][0] = a.m[1][0] * b;
    result.m[1][1] = a.m[1][1] * b;
    result.m[1][2] = a.m[1][2] * b;
    result.m[2][0] = a.m[2][0] * b;
    result.m[2][1] = a.m[2][1] * b;
    result.m[2][2] = a.m[2][2] * b;
    return result;
}

inline mat3 mat3_mult(mat3 a, mat3 b) {
    mat3 result;
    result.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] +
                     a.m[0][2] * b.m[2][0];
    result.m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] +
                     a.m[0][2] * b.m[2][1];
    result.m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] +
                     a.m[0][2] * b.m[2][2];
    result.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] +
                     a.m[1][2] * b.m[2][0];
    result.m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] +
                     a.m[1][2] * b.m[2][1];
    result.m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] +
                     a.m[1][2] * b.m[2][2];
    result.m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] +
                     a.m[2][2] * b.m[2][0];
    result.m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] +
                     a.m[2][2] * b.m[2][1];
    result.m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] +
                    a.m[2][2] * b.m[2][2];
    return result;
}

#endif
