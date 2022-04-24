#ifndef __MAT4_H__
#define __MAT4_H__

#include "vec4.h"

struct mat4 {
    float m[4][4];
};

inline mat4 mat4_make(vec4 a, vec4 b, vec4 c, vec4 d) {
    mat4 result;
    result.m[0][0] = a.x;
    result.m[0][1] = a.y;
    result.m[0][2] = a.z;
    result.m[0][3] = a.w;
    result.m[1][0] = b.x;
    result.m[1][1] = b.y;
    result.m[1][2] = b.z;
    result.m[1][3] = b.w;
    result.m[2][0] = c.x;
    result.m[2][1] = c.y;
    result.m[2][2] = c.z;
    result.m[2][3] = c.w;
    result.m[3][0] = d.x;
    result.m[3][1] = d.y;
    result.m[3][2] = d.z;
    result.m[3][3] = d.w;
    return result;
}

inline mat4 mat4_identity() {
    mat4 result;
    result.m[0][0] = 1;
    result.m[0][1] = 0;
    result.m[0][2] = 0;
    result.m[0][3] = 0;
    result.m[1][0] = 0;
    result.m[1][1] = 1;
    result.m[1][2] = 0;
    result.m[1][3] = 0;
    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = 1;
    result.m[2][3] = 0;
    result.m[3][0] = 0;
    result.m[3][1] = 0;
    result.m[3][2] = 0;
    result.m[3][3] = 1;
    return result;
}

inline mat4 mat4_zero() {
    mat4 result;
    result.m[0][0] = 0;
    result.m[0][1] = 0;
    result.m[0][2] = 0;
    result.m[0][3] = 0;
    result.m[1][0] = 0;
    result.m[1][1] = 0;
    result.m[1][2] = 0;
    result.m[1][3] = 0;
    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = 0;
    result.m[2][3] = 0;
    result.m[3][0] = 0;
    result.m[3][1] = 0;
    result.m[3][2] = 0;
    result.m[3][3] = 0;
    return result;
}

inline mat4 mat4_inverse(mat4 a) {
    mat4 result;
    float det = a.m[0][0] * (a.m[1][1] * a.m[2][2] - a.m[2][1] * a.m[1][2]) -
                a.m[0][1] * (a.m[1][0] * a.m[2][2] - a.m[2][0] * a.m[1][2]) +
                a.m[0][2] * (a.m[1][0] * a.m[2][1] - a.m[2][0] * a.m[1][1]);
    if (det == 0) {
        return mat4_zero();
    }

    det = 1.0f / det;
    result.m[0][0] = det * (a.m[1][1] * a.m[2][2] - a.m[2][1] * a.m[1][2]);
    result.m[0][1] = det * (a.m[0][2] * a.m[2][1] - a.m[0][1] * a.m[2][2]);
    result.m[0][2] = det * (a.m[0][1] * a.m[1][2] - a.m[0][2] * a.m[1][1]);
    result.m[0][3] = 0.0f;
    result.m[1][0] = det * (a.m[1][2] * a.m[2][0] - a.m[1][0] * a.m[2][2]);
    result.m[1][1] = det * (a.m[0][0] * a.m[2][2] - a.m[0][2] * a.m[2][0]);
    result.m[1][2] = det * (a.m[0][2] * a.m[1][0] - a.m[0][0] * a.m[1][2]);
    result.m[1][3] = 0.0f;
    result.m[2][0] = det * (a.m[1][0] * a.m[2][1] - a.m[2][0] * a.m[1][1]);
    result.m[2][1] = det * (a.m[2][0] * a.m[0][1] - a.m[0][0] * a.m[2][1]);
    result.m[2][2] = det * (a.m[0][0] * a.m[1][1] - a.m[0][1] * a.m[1][0]);
    result.m[2][3] = 0.0f;
    result.m[3][0] = -(result.m[0][0] * a.m[3][0] + result.m[1][0] * a.m[3][1] + result.m[2][0] * a.m[3][2]);
    result.m[3][1] = -(result.m[0][1] * a.m[3][0] + result.m[1][1] * a.m[3][1] + result.m[2][1] * a.m[3][2]);
    result.m[3][2] = -(result.m[0][2] * a.m[3][0] + result.m[1][2] * a.m[3][1] + result.m[2][2] * a.m[3][2]);
    result.m[3][3] = 1.0f;

    return result;
}

inline mat4 mat4_scalr(mat4 a, float b) {
    mat4 result;
    result.m[0][0] = a.m[0][0] * b;
    result.m[0][1] = a.m[0][1] * b;
    result.m[0][2] = a.m[0][2] * b;
    result.m[0][3] = a.m[0][3] * b;
    result.m[1][0] = a.m[1][0] * b;
    result.m[1][1] = a.m[1][1] * b;
    result.m[1][2] = a.m[1][2] * b;
    result.m[1][3] = a.m[1][3] * b;
    result.m[2][0] = a.m[2][0] * b;
    result.m[2][1] = a.m[2][1] * b;
    result.m[2][2] = a.m[2][2] * b;
    result.m[2][3] = a.m[2][3] * b;
    result.m[3][0] = a.m[3][0] * b;
    result.m[3][1] = a.m[3][1] * b;
    result.m[3][2] = a.m[3][2] * b;
    result.m[3][3] = a.m[3][3] * b;
    return result;
}

inline mat4 mat4_mul(mat4 a, mat4 b) {
    mat4 result;

    result.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0] + a.m[0][3] * b.m[3][0];
    result.m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1] + a.m[0][3] * b.m[3][1];
    result.m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2] + a.m[0][3] * b.m[3][2];
    result.m[0][3] = a.m[0][0] * b.m[0][3] + a.m[0][1] * b.m[1][3] + a.m[0][2] * b.m[2][3] + a.m[0][3] * b.m[3][3];
    result.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0] + a.m[1][3] * b.m[3][0];
    result.m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1] + a.m[1][3] * b.m[3][1];
    result.m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2] + a.m[1][3] * b.m[3][2];
    result.m[1][3] = a.m[1][0] * b.m[0][3] + a.m[1][1] * b.m[1][3] + a.m[1][2] * b.m[2][3] + a.m[1][3] * b.m[3][3];
    result.m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0] + a.m[2][3] * b.m[3][0];
    result.m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1] + a.m[2][3] * b.m[3][1];
    result.m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2] + a.m[2][3] * b.m[3][2];
    result.m[2][3] = a.m[2][0] * b.m[0][3] + a.m[2][1] * b.m[1][3] + a.m[2][2] * b.m[2][3] + a.m[2][3] * b.m[3][3];
    result.m[3][0] = a.m[3][0] * b.m[0][0] + a.m[3][1] * b.m[1][0] + a.m[3][2] * b.m[2][0] + a.m[3][3] * b.m[3][0];
    result.m[3][1] = a.m[3][0] * b.m[0][1] + a.m[3][1] * b.m[1][1] + a.m[3][2] * b.m[2][1] + a.m[3][3] * b.m[3][1];
    result.m[3][2] = a.m[3][0] * b.m[0][2] + a.m[3][1] * b.m[1][2] + a.m[3][2] * b.m[2][2] + a.m[3][3] * b.m[3][2];
    result.m[3][3] = a.m[3][0] * b.m[0][3] + a.m[3][1] * b.m[1][3] + a.m[3][2] * b.m[2][3] + a.m[3][3] * b.m[3][3];
    return result;
}

#endif
