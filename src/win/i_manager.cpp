#include "i_manager.h"

#include <iostream>

void GLFWMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    InputManager* inputManager = (InputManager*)glfwGetWindowUserPointer(window);
    
    for (auto& listener : inputManager->mouseWheelListeners)
    {
        listener(xoffset, yoffset);
    }
}

void GLFWMousePosCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    InputManager* inputManager = (InputManager*)glfwGetWindowUserPointer(window);
    
    for (auto& listener : inputManager->mouseListeners)
    {
        listener(xposIn, yposIn);
    }
}

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update(GLFWwindow* window)
{
    InputManager* inputManager = (InputManager*)glfwGetWindowUserPointer(window);
    
    for (auto& listener : inputManager->keyListeners)
    {
        listener(window);
    }
}

void InputManager::AddKeyListener(std::function<void(GLFWwindow*)> listener)
{
    keyListeners.push_back(listener);
}

void InputManager::AddMouseListener(std::function<void(double, double)> listener)
{
    mouseListeners.push_back(listener);
}

void InputManager::AddMouseWheelListener(std::function<void(double, double)> listener)
{
    mouseWheelListeners.push_back(listener);
}
