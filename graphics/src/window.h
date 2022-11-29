#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool frameBufferResized;
  size_t width;
  size_t height;
  char *name;
  GLFWwindow *glfwWindow;
} Window;

Window *window_init(Window window[static 1], size_t width, size_t height,
                    const char *name, GLFWwindow *glfwWindow);
void window_destroy(Window window[static 1]);
VkExtent2D getExtent(const Window window[static 1]);
bool shouldClose(const Window window[static 1]);
void createWindow(const Window window[static 1], VkInstance instance,
                  VkSurfaceKHR surface[static 1]);
void frameBufferResizeCallback(GLFWwindow *glfwWindow, int width, int height);
