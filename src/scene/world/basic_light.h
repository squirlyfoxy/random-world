#ifndef __BASIC_LIGHT_H__
#define __BASIC_LIGHT_H__

#include "../../proc/shaders/shaders.h"

//Light commons
#include "light.h"

class BasicLight {
public:
    // Basic diffused light
    BasicLight(vec3 pos, vec4 color);
    BasicLight();

    void Bind(Program &p, int i = 0);

    vec3    gPosition;
    vec4    gColor;
    vec3    gAmbient;
    vec3    gDiffuse;
    vec3    gSpecular;
};

#endif
