#ifndef __H_WINDOW__
#define __H_WINDOW__

//GLFW
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "i_manager.h"
#include "../scene/world/world.h"

struct Window {
    GLFWwindow* window;
    float deltaTime;
    int width;
    int height;

    //Window input manager
    InputManager inputManager;
};

extern World* world;
extern Window window_t;

int NewWindow(int width, int height, const char* title);
void EnterLoop();

#endif
