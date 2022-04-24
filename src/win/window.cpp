#include <cstdlib>
#include <cstdio>

#include <glad/glad.h>
#include <cpmath/act/act_mat4.h>

#include "window.h"
#include "../t.h"

#include "../proc/shaders/shaders.h"
#include "../proc/texture.h"
//#include "../proc/framebuffer.h"
#include "../scene/camera.h"
#include "../scene/obj_3d.h"

Window window_t;
World* world;

static void ResizeCallback(GLFWwindow* window, int width, int height) {
    window_t.width = width;
    window_t.height = height;

    glViewport(0, 0, width, height);
    camera_mutex.lock();
    camera_aspect = (float)window_t.width / (float)window_t.height;
    camera_update_matrix();

    // Framebuffers
    /*DestroyFramebuffer();
    GenerateFramebuffer(window_t.width, window_t.height);*/
}

bool polly_mode = false;
void polly_mode_callback(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) {
        if (!polly_mode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            polly_mode = true;
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            polly_mode = false;
        }
    }
}

static void ErrorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

int NewWindow(int width, int height, const char* title) {
    std::cout << "Creating window..." << std::endl;
    window_t.width = width;
    window_t.height = height;

    glfwSetErrorCallback(ErrorCallback); //Callback for errors
    
    if (!glfwInit()) {
        return FAIL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // MSAA 4x
    glfwWindowHint(GLFW_SAMPLES, 4);

    //Create a new window
    window_t.window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window_t.window) {
        glfwTerminate();
        return FAIL;
    }

    //Context
    glfwMakeContextCurrent(window_t.window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return FAIL;
    }

    //Disable vsync
    glfwSwapInterval(0);

    glfwSetInputMode(window_t.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    glfwSetWindowSizeCallback(window_t.window, ResizeCallback);

    //Input callbacks
    glfwSetCursorPosCallback(window_t.window, GLFWMousePosCallback);
    glfwSetScrollCallback(window_t.window, GLFWMouseWheelCallback);

    window_t.inputManager.AddMouseListener(camera_mouse_callback);
    window_t.inputManager.AddKeyListener(polly_mode_callback);
    window_t.inputManager.AddKeyListener(camera_keyboard_callback);

    //glfwSetCursorPosCallback(window_t.window, mouse_callback);
    
    //Set a poiter to the window
    glfwSetWindowUserPointer(window_t.window, &window_t.inputManager);

    //Viewport
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    //Cullface
    glEnable(GL_CULL_FACE);  
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    // Gamma correction
    glEnable(GL_FRAMEBUFFER_SRGB);

    //Antialiasing (Line smoothing)
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // MSAA
    glEnable(GL_MULTISAMPLE);

    //GenerateFramebuffer(width, height);

    world = new World();

    return SUCCESS;
}

void EnterLoop() {
    camera_fov = DEG_TO_RAD(60.0f);
    camera_far = 1000.0f;
    camera_near = 0.1f;
    camera_aspect = (float)window_t.width / (float)window_t.height;

    static double lastTime = glfwGetTime();
    static int frames = 0;

    camera_update_matrix();
    while (!glfwWindowShouldClose(window_t.window)) {
        //Update keyboard input
        window_t.inputManager.Update(window_t.window);

        //fps
        double currentTime = glfwGetTime();
        window_t.deltaTime = currentTime - lastTime;

        //If 1 second passed, print fps
        if (window_t.deltaTime >= 1.0) {
            std::cout << "FPS: " << frames << std::endl;
            lastTime = currentTime;
            frames = 0;
        }

        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        world->Render();

        glfwSwapBuffers(window_t.window);
        glfwPollEvents();

        frames++;
    }

    glfwDestroyWindow(window_t.window);
    glfwTerminate();
}
