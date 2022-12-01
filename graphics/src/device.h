#pragma once
#include "window.h"
#include <stdbool.h>
#include <stdint.h>
#include <vulkan/vulkan_core.h>

#ifdef DEBUG
static const bool WANT_VALIDATION_LAYERS = true;
#else
static const bool WANT_VALIDATION_LAYERS = false;
#endif

#define VALIDATION_LAYERS_COUNT 1
#define DEVICE_EXTENSIONS_COUNT 1

/* only using the debugging layer....for now */
static const char *VALIDATION_LAYERS[VALIDATION_LAYERS_COUNT] = {
    "VK_LAYER_KHRONOS_validation"};

/* list of required device extension */
static const char *DEVICE_EXTENSIONS[DEVICE_EXTENSIONS_COUNT] = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME};

typedef struct {
  uint32_t graphicsFamily;
  bool hasGraphicsFamily;
} GraphicsFamily;

typedef struct {
  uint32_t presentFamily;
  bool hasPresentFamily;
} PresentFamily;

typedef struct {
  PresentFamily presentFamily;
  GraphicsFamily graphicsFamily;
} QueueFamilyIndices;

typedef struct {
  VkSurfaceFormatKHR *formats;
  uint32_t count;
} SurfaceSupportedFormats;

typedef struct {
  VkPresentModeKHR *modes;
  uint32_t count;
} SurfacePresentationMode;

/* A SwapChainSupportDetails contains:
 * basic surface capabilities (min/max number of images in swap chain, min/max
 * width and height of images)
 * surface formats (pixel format, color space)
 * available presentation modes
 */
typedef struct {
  VkSurfaceCapabilitiesKHR capabilities;
  SurfaceSupportedFormats surfaceFormats;
  SurfacePresentationMode surfacePresentModes;
} SwapChainSupportDetails;

typedef struct {
  VkInstance instance;
  // an abstract type surface that establish a connection with WSI (window
  // system integration) to present results on the screen
  VkSurfaceKHR surface;

  // debug callback handle
  VkDebugUtilsMessengerEXT debugMessenger;

  // graphic card that we select
  VkPhysicalDevice physicalDevice;

  // logical device that interfaces with the physical device
  VkDevice device;

  //
  VkCommandPool commandPool;

  // device lifetime depends on the window we are using
  Window *window;

  // handle to graphics queue
  VkQueue graphicsQueue;

  // handle to presentation queue
  VkQueue presentQueue;

  VkPhysicalDeviceProperties properties;

} Device;

void device_init(Device device[static 1], Window window[static 1]);
void device_destroy(Window window[static 1]);

void findQueueFamilies(QueueFamilyIndices queue[static 1],
                       VkPhysicalDevice device, VkSurfaceKHR surface);
bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
void createInstance(Device device[static 1]);
void setupDebugMessenger(Device device[static 1]);
void populateDebugMessengerCreateInfo(
    VkDebugUtilsMessengerCreateInfoEXT createInfo[static 1]);
bool checkDeviceExtensionsSupport(const VkPhysicalDevice device);
void createLogicalDevice(Device device[static 1]);
void createCommandPool(Device device[static 1]);
void createImageWithInfo(const Device device[static 1],
                         const VkImageCreateInfo imageInfo[static 1],
                         VkMemoryPropertyFlags properties,
                         VkImage image[static 1],
                         VkDeviceMemory imageMemory[static 1]);
uint32_t findMemoryType(const Device device[static 1], uint32_t typeFilter,
                        VkMemoryPropertyFlags properties);
VkFormat findSupportedFormat(const Device device[static 1],
                             const VkFormat *candidates, VkImageTiling tiling,
                             VkFormatFeatureFlags features);
void createBuffer(const Device device[static 1], VkDeviceSize size,
                  VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                  VkBuffer buffer[static 1],
                  VkDeviceMemory bufferMemory[static 1]);
VkCommandBuffer beginSingleTimeCommands(const Device device[static 1]);
void endSingleTimeCommands(const Device device[static 1],
                           VkCommandBuffer commandBuffer);
void copyBuffer(const Device device[static 1], VkBuffer srcBuffer,
                VkBuffer dstBuffer, VkDeviceSize size);
void copyBufferToImage(const Device device[static 1], VkBuffer buffer,
                       VkImage image, uint32_t width, uint32_t height,
                       uint32_t layerCount);
/*
 * Caller must free SwapChainSupportDetails surfaceFormats and
 * surfacePresentModes
 */
void querySwapChainSupport(SwapChainSupportDetails details[static 1],
                           VkPhysicalDevice device, VkSurfaceKHR surface);

static VkResult create_debug_utils_messengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pDebugMessenger) {
  PFN_vkCreateDebugUtilsMessengerEXT func =
      (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
          instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != (void *)0) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}