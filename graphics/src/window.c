#include "window.h"

Window *window_init(Window window[static 1], size_t width, size_t height,
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

VkExtent2D getExtent(const Window window[static 1]);
