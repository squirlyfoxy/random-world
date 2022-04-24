#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__

#include "light.h"

class DirectionalLight {
public:
    DirectionalLight(vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular);
    DirectionalLight();

    vec3    gDirection;
    vec3    gAmbient;
    vec3    gDiffuse;
    vec3    gSpecular;
};

#endif
