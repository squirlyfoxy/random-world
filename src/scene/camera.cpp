#include "camera.h"

#include <GLFW/glfw3.h>

#include <cpmath/act/act_mat4.h>

#include "world/world.h"
#include "../win/window.h"

float camera_fov;
float camera_aspect;
float camera_near;
float camera_far;
bool camera_moved = false;

vec3  camera_position   = vec3_make(0.0f, 10.0f, 0.0f);
vec3  camera_front      = vec3_make(0.0f, 0.0f, -1.0f);
vec3  camera_up         = vec3_make(0.0f, 1.0f, 0.0f);

mat4  camera_view_matrix;

std::mutex camera_mutex;

mat4 camera_perspective_projection() {
    return mat4_perspective(camera_fov, camera_aspect, camera_near, camera_far);
}

void camera_update_matrix() {
    camera_mutex.lock();
    camera_view_matrix = mat4_look_at(camera_position, vec3_add(camera_position, camera_front), camera_up);
    camera_mutex.unlock();
}

// ********************
// Camera input callbacks

float yaw   = 0.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX = 0, lastY = 0;
bool firstMouse = true;
void camera_mouse_callback(double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    if (yaw > 360.0f)
        yaw -= 360.0f;
    if (yaw < 0.0f)
        yaw += 360.0f;

    vec3 front = vec3_make(cos(DEG_TO_RAD(yaw)) * cos(DEG_TO_RAD(pitch)), sin(DEG_TO_RAD(pitch)), sin(DEG_TO_RAD(yaw)) * cos(DEG_TO_RAD(pitch)));
    camera_mutex.lock();
    camera_front = normalize(front);
    camera_mutex.unlock();

    camera_update_matrix();
}

void camera_keyboard_callback(GLFWwindow* win) {
    const float cameraSpeed = 0.05f;
    camera_moved = false;

    camera_mutex.lock();
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
        camera_position = vec3_sub(camera_position, vec3_multiply(camera_front, cameraSpeed));
        camera_moved = true;
    }
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
        camera_position = vec3_add(camera_position, vec3_multiply(camera_front, cameraSpeed));
        camera_moved = true;
    }
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
        camera_position = vec3_sub(camera_position, vec3_multiply(normalize(vec3_cross(camera_front, camera_up)), cameraSpeed));
        camera_moved = true;
    }
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
        camera_position = vec3_add(camera_position, vec3_multiply(normalize(vec3_cross(camera_front, camera_up)), cameraSpeed));
        camera_moved = true;
    }
    camera_mutex.unlock();

    //If camera moved, create a new chunk
    if (camera_moved) {
        camera_update_matrix();
    }
}
