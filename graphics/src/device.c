#include "device.h"
#include "errors.h"
#include <string.h>
#include <vulkan/vulkan_core.h>

bool checkDeviceExtensionsSupport(const VkPhysicalDevice device) {
  uint32_t extensionCount;
  vkEnumerateDeviceExtensionProperties(device, (void *)0, &extensionCount,
                                       (void *)0);
  VkExtensionProperties *availableExtensions =
      malloc(sizeof(VkExtensionProperties) * extensionCount);
  if (!availableExtensions) {
    errno_abort("Allocating memory VkExtensionProperties");
  }
  vkEnumerateDeviceExtensionProperties(device, (void *)0, &extensionCount,
                                       availableExtensions);
  bool hasSupport = false;
  for (size_t i = 0; i < extensionCount; i++) {
    const char *available_extension = availableExtensions[i].extensionName;
    // TODO: do I need to loop thru all of them, since I am only using one at
    // the moment...
    for (size_t j = 0; j < DEVICE_EXTENSIONS_COUNT; j++) {
      const char *device_extension = DEVICE_EXTENSIONS[j];
      if (strncmp(device_extension, available_extension,
                  VK_MAX_EXTENSION_NAME_SIZE) == 0) {
        hasSupport = true;
      }
    }
  }
  free(availableExtensions);
  return hasSupport;
}

bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
  QueueFamilyIndices queue;
  findQueueFamilies(&queue, device, surface);
  bool swapChainAdequate = false;
  bool extensionsSupported = checkDeviceExtensionsSupport(device);
  if (extensionsSupported) {
    SwapChainSupportDetails swapChainSupport;
    querySwapChainSupport(&swapChainSupport, device, surface);
    swapChainAdequate = !swapChainSupport.surfaceFormats.count &&
                        !swapChainSupport.surfacePresentModes.count;
    free(swapChainSupport.surfaceFormats.formats);
    free(swapChainSupport.surfacePresentModes.modes);
  }

  VkPhysicalDeviceFeatures supportedFeatures;
  vkGetPhysicalDeviceFeatures(device, &supportedFeatures);
  return queue.graphicsFamily.hasGraphicsFamily &&
         queue.presentFamily.hasPresentFamily && extensionsSupported &&
         swapChainAdequate && supportedFeatures.samplerAnisotropy;
}

void querySwapChainSupport(SwapChainSupportDetails details[static 1],
                           VkPhysicalDevice device, VkSurfaceKHR surface) {
  // basic surface capabilities
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface,
                                            &details->capabilities);

  vkGetPhysicalDeviceSurfaceFormatsKHR(
      device, surface, &details->surfaceFormats.count, (void *)0);
  if (details->surfaceFormats.count != 0) {
    details->surfaceFormats.formats =
        malloc(sizeof(VkSurfaceFormatKHR) * details->surfaceFormats.count);
    if (!details->surfaceFormats.formats) {
      errno_abort("Allocating memory for VkSurfaceFormatKHR");
    }

    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface,
                                         &details->surfaceFormats.count,
                                         details->surfaceFormats.formats);
  }

  vkGetPhysicalDeviceSurfacePresentModesKHR(
      device, surface, &details->surfacePresentModes.count, (void *)0);
  if (details->surfacePresentModes.count != 0) {
    details->surfacePresentModes.modes =
        malloc(sizeof(VkPresentModeKHR) * details->surfacePresentModes.count);
    if (!details->surfacePresentModes.modes) {
      errno_abort("Allocating memory for VkPresentModeKHR");
    }
    vkGetPhysicalDeviceSurfacePresentModesKHR(
        device, surface, &details->surfacePresentModes.count,
        details->surfacePresentModes.modes);
  }
}

void setupDebugMessenger(Device device[static 1]) {
  if (!WANT_VALIDATION_LAYERS) {
    return;
  }
  VkDebugUtilsMessengerCreateInfoEXT create_info;
  populateDebugMessengerCreateInfo(&create_info);

  VkResult result = create_debug_utils_messengerEXT(
      device->instance, &create_info, (void *)0, &device->debugMessenger);
  if (result != VK_SUCCESS) {
    error_abort(result, "failed to set up debug messenger!");
  }
}

bool hasValidationLayerSupport() {
  uint32_t layer_count;
  // get the number of available layer properties
  vkEnumerateInstanceLayerProperties(&layer_count, (void *)0);

  VkLayerProperties *available_layers =
      malloc(sizeof(VkLayerProperties) * layer_count);
  if (!available_layers) {
    errno_abort("Allocating VkLayerProperties");
  }
  // get the layer properties
  vkEnumerateInstanceLayerProperties(&layer_count, available_layers);

  bool layerFound = false;
  for (size_t i = 0; i < VALIDATION_LAYERS_COUNT; i++) {
    layerFound = false;
    const char *layer_name = VALIDATION_LAYERS[i];
    for (size_t j = 0; j < layer_count; j++) {
      VkLayerProperties available_layer = available_layers[j];
      if (strcmp(layer_name, available_layer.layerName) == 0) {
        layerFound = true;
        break;
      }
    }
    if (!layerFound) {
      break;
    }
  }
  free(available_layers);
  return layerFound;
}

void checkGlfwRequiredInstanceExtensions(const char *const *glfw_extensions,
                                         size_t count) {
  uint32_t extension_count = 0;
  vkEnumerateInstanceExtensionProperties((void *)0, &extension_count,
                                         (void *)0);
  VkExtensionProperties *extensions =
      malloc(sizeof(VkExtensionProperties) * extension_count);
  if (!extensions) {
    errno_abort("Allocating VkExtensionProperties");
  }
  vkEnumerateInstanceExtensionProperties((void *)0, &extension_count,
                                         extensions);

  DPRINTF(("available extensions: "));
  for (size_t i = 0; i < extension_count; i++) {
    DPRINTF(("%s", extensions[i].extensionName));
  }

  DPRINTF(("required extensions: "));
  for (size_t i = 0; i < count; i++) {
    DPRINTF(("\t%s", glfw_extensions[i]));
    bool found = false;
    for (size_t j = 0; j < extension_count; j++) {
      if (strcmp(glfw_extensions[i], extensions[j].extensionName) == 0) {
        found = true;
        break;
      }
    }
    if (!found) {
      error_abort(-1, "Missing required glfw extension");
    }
  }
  free(extensions);
}

void device_init(Device device[static 1], Window window[static 1]) {
  device->window = window;
  createInstance(device);
  setupDebugMessenger(device);
}

void createInstance(Device device[static 1]) {
  if (WANT_VALIDATION_LAYERS && hasValidationLayerSupport()) {
    error_abort(-1, "validation layers requested, but not available!");
  }

  // provides useful information to the driver in order to optimize
  VkApplicationInfo appInfo = {.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                               .pApplicationName = "liby",
                               .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                               .pEngineName = "No Engine",
                               .engineVersion = VK_MAKE_VERSION(1, 0, 0),
                               .apiVersion = VK_API_VERSION_1_3};

  // tells the vulkan driver which global extensions and validation layers we
  // want to use. applies to entire program.
  VkInstanceCreateInfo createInfo = {.sType =
                                         VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                                     .pApplicationInfo = &appInfo};

  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions;
  const char **extensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  if (WANT_VALIDATION_LAYERS) {
    extensions = malloc(sizeof(char *) * glfwExtensionCount + 1);
    if (!extensions) {
      errno_abort("Allocating extensions");
    }
    for (size_t i = 0; i < glfwExtensionCount; i++) {
      extensions[i] = malloc(sizeof(char) * strlen(glfwExtensions[i]));
      if (!extensions[i]) {
        errno_abort("Allocating space for glfw extension name");
      }
      extensions[i] = strdup(glfwExtensions[i]);
      if (!extensions[i]) {
        errno_abort("Copying glfw extension name");
      }
    }
    // since I am passing a custom copy of extensions, I should delete the one
    // returned...
    extensions[glfwExtensionCount] =
        malloc(sizeof(char) * strlen(VK_EXT_DEBUG_UTILS_EXTENSION_NAME));
    if (!extensions[glfwExtensionCount]) {
      errno_abort("Allocating debug validation layer");
    }
    extensions[glfwExtensionCount] = strdup(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    if (!extensions[glfwExtensionCount]) {
      errno_abort("Copying debug utils extension name");
    }
    glfwExtensionCount++;
    createInfo.ppEnabledExtensionNames = extensions;
    free(glfwExtensions);
  } else {
    createInfo.ppEnabledExtensionNames = glfwExtensions;
  }

  // get extension needed to interface with the window system.
  createInfo.enabledExtensionCount = glfwExtensionCount;
  createInfo.enabledLayerCount = 0;

  checkGlfwRequiredInstanceExtensions(createInfo.ppEnabledExtensionNames,
                                      glfwExtensionCount);

  VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;

  if (WANT_VALIDATION_LAYERS) {
    createInfo.enabledLayerCount = (uint32_t)VALIDATION_LAYERS_COUNT;
    createInfo.ppEnabledLayerNames = VALIDATION_LAYERS;
    debugCreateInfo.pUserData = (void *)0;
    populateDebugMessengerCreateInfo(&debugCreateInfo);
    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
  } else {
    createInfo.enabledLayerCount = 0;
    createInfo.pNext = (void *)0;
  }

  VkResult result = vkCreateInstance(&createInfo, (void *)0, &device->instance);
  if (result != VK_SUCCESS) {
    error_abort(result, "failed to create instance");
  }
}
