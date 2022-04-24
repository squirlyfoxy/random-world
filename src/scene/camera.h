#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GLFW/glfw3.h> //For scancodes

#include <cpmath/cpmath.h>

#include <mutex>

//Perspective camera

// *************************
// Camera informations

//in radiants
extern float camera_fov;

extern float camera_aspect;
extern float camera_near;
extern float camera_far;
extern float yaw;
extern float pitch;
extern bool camera_moved;
extern vec3  camera_position;

extern std::mutex camera_mutex;

// *************************
// Camera view matrix

extern mat4  camera_view_matrix;

mat4 camera_perspective_projection();
void camera_update_matrix();

void camera_mouse_callback(double xposIn, double yposIn);
void camera_keyboard_callback(GLFWwindow* win);

#endif
