#ifndef __CP_MATH_ACT_3D_H__
#define __CP_MATH_ACT_3D_H__

#include <math.h>

#include "../com/vec3.h"

inline bool is_object_in_camera_view(vec3 obj_position, vec3 camera_position, float camera_yaw, float camera_fov, float mul = 2.3f)
{
    float angle = atan2(obj_position.x - camera_position.x, obj_position.z - camera_position.z);
    float angle_diff = angle - camera_yaw;
    if (angle_diff < -3.14)
        angle_diff += 2 * 3.14;
    if (angle_diff > 3.14)
        angle_diff -= 2 * 3.14;

    return abs(angle_diff) < camera_fov * mul;
}

#endif
