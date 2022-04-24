#include "directional_light.h"

DirectionalLight::DirectionalLight(vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular)
{
    gDirection = direction;
    gAmbient = ambient;
    gDiffuse = diffuse;
    gSpecular = specular;
}

DirectionalLight::DirectionalLight()
{
    gDirection = vec3_make(-0.2f, -1.0f, -0.3f);
    gAmbient = vec3_make(0.2f, 0.2f, 0.2f);
    gDiffuse = vec3_make(0.5f, 0.5f, 0.5f);
    gSpecular = vec3_make(1.0f, 1.0f, 1.0f);
}
