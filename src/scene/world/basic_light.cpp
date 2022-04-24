#include "basic_light.h"

#include <glad/glad.h>
#include <cpmath/act/act_mat4.h>

#include "../camera.h"

BasicLight::BasicLight(vec3 pos, vec4 color) {
    gPosition = pos;
    gColor = color;

    gAmbient = vec3_make(0.2f, 0.2f, 0.2f);
    gDiffuse = vec3_make(0.5f, 0.5f, 0.5f);
    gSpecular = vec3_make(1.0f, 1.0f, 1.0f);
}

BasicLight::BasicLight() {
    gPosition = vec3_make(0, 0, 0);
    gColor = vec4_make(1.0f, 1.0f, 1.0f, 1.0f);
    gAmbient = vec3_make(0.2f, 0.2f, 0.2f);
    gDiffuse = vec3_make(0.5f, 0.5f, 0.5f);
    gSpecular = vec3_make(1.0f, 1.0f, 1.0f);
}

void BasicLight::Bind(Program &p, int i) {
    BindVec3(p, "lights[" + std::to_string(i) + "].lightPos", gPosition);
    BindVec4(p, "lights[" + std::to_string(i) + "].lightColor", gColor);
    BindVec3(p, "lights[" + std::to_string(i) + "].ambient", gAmbient);
    BindVec3(p, "lights[" + std::to_string(i) + "].diffuse", gDiffuse);
    BindVec3(p, "lights[" + std::to_string(i) + "].specular", gSpecular);
}
