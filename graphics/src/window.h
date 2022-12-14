#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool frameBufferResized;
  uint32_t width;
  uint32_t height;
  char *name;
  GLFWwindow *glfwWindow;
} Window;

Window *window_init(Window window[static 1], uint32_t width, uint32_t height,
                    const char *name);
void window_destroy(Window window[static 1]);
VkExtent2D getExtent(const Window window[static 1]);
bool shouldClose(const Window window[static 1]);
void createWindowSurface(const Window window[static 1], VkInstance instance,
                         VkSurfaceKHR surface[static 1]);
void frameBufferResizeCallback(GLFWwindow *glfwWindow, int width, int height);
