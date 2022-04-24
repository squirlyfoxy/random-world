#ifndef __I_MANAGER_H__
#define __I_MANAGER_H__

#include <GLFW/glfw3.h>

#include <functional>
#include <vector>

void GLFWMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
void GLFWMousePosCallback(GLFWwindow* window, double xposIn, double yposIn);

class InputManager {
public:
    InputManager();
    ~InputManager();

    void AddKeyListener(std::function<void(GLFWwindow*)> listener);
    void AddMouseListener(std::function<void(double, double)> listener);
    void AddMouseWheelListener(std::function<void(double, double)> listener);

    void Update(GLFWwindow* window);

    std::vector<std::function<void(GLFWwindow*)>> keyListeners;
    std::vector<std::function<void(double, double)>> mouseListeners;
    std::vector<std::function<void(double, double)>> mouseWheelListeners;
private:
};

#endif
