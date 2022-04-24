#ifndef __LIGHT_H__
#define __LIGHT_H__

#define AMBIENT_STRETCH_FACTOR  0.1f
#define SPECULAR_STRETCH_FACTOR 0.5f

#define LIGHT_NEAR_PLANE    1.0f
#define LIGHT_FAR_PLANE     7.5f

#include <cpmath/cpmath.h>

struct Material {
    int     diffuse =   0;
    int     specular =  1;
    float   shininess;
    bool    can_reflect;
};

void LightSpaceTransform(vec3 pos, mat4* view, mat4* projection);

#endif
