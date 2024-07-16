#include "GLFW/glfw3.h"
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include "globals.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int createWindow() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
    if (!Monitor) {
        return 1;
    }

    globals::screenWidth = glfwGetVideoMode(Monitor)->width;
    globals::screenHeight = glfwGetVideoMode(Monitor)->height;

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, true);
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_MAXIMIZED, true);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

    globals::window = glfwCreateWindow(globals::screenWidth, globals::screenHeight, "External overlay", nullptr, nullptr);
    if (globals::window == nullptr)
        return 1;

    glfwMakeContextCurrent(globals::window);
    glfwSwapInterval(1);
}