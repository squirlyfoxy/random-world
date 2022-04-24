#include "light.h"

#include <cpmath/act/act_mat4.h>

void LightSpaceTransform(vec3 pos, mat4* view, mat4* projection) {
    mat4 light_view_matrix = mat4_look_at(pos, vec3_make(0, 0, 0), vec3_make(0, 1, 0));
    mat4 light_projection_matrix = mat4_perspective(45.0f, 1.0f, LIGHT_NEAR_PLANE, LIGHT_FAR_PLANE);
    *view = light_view_matrix;
    *projection = light_projection_matrix;
}
