#include "window.h"

Window *window_init(Window window[static 1], uint32_t width, uint32_t height,
                    const char *name) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  window->glfwWindow = glfwCreateWindow(width, height, name, (void*)0, (void*)0);
  window->name = strndup(name, strlen(name));
  glfwSetWindowUserPointer(window->glfwWindow, window);
  glfwSetFramebufferSizeCallback(window->glfwWindow, frameBufferResizeCallback);

  return window;
}

void window_destroy(Window window[static 1]) {
  glfwDestroyWindow(window->glfwWindow);
  glfwTerminate();
  if (window->name) {
    free(window->name);
  }
}

VkExtent2D getExtent(const Window window[static 1]) {
  VkExtent2D extent = { .width = window->width, .height = window->height };
  return extent;
}

// TODO: is this function really needed
bool shouldClose(const Window window[static 1]) {
  return glfwWindowShouldClose(window->glfwWindow);
}

// TODO: is this function really needed
void createWindowSurface(const Window window[static 1], VkInstance instance,
                  VkSurfaceKHR surface[static 1]) {
  if (glfwCreateWindowSurface(instance, window->glfwWindow, (void*)0, surface) != VK_SUCCESS) {
    fprintf(stderr, "Failed to create window surface"); 
  }
}

void frameBufferResizeCallback(GLFWwindow *glfwWindow, int width, int height) {
  Window *window = (Window *)glfwGetWindowUserPointer(glfwWindow);
  window->frameBufferResized = true;
  window->width = (uint32_t)width;
  window->height = (uint32_t)height;
}
