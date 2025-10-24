#define GLFW_INCLUDE_VULKAN

#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>

const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;

const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#pragma message("enableValidationLayers=false")
#else
const bool enableValidationLayers = true;
#pragma message("enableValidationLayers=true")
#endif


std::string strVecFormat(const std::vector<const char *> &vec) {
    std::string formatted = "{";
    int idx = -1;
    for (auto el: vec) {
        idx += 1;
        formatted += std::string(el);
        if (!idx + 1 == vec.size()) {
            formatted += ", ";
        }
    }
    formatted += "}";
    return formatted;
}


bool checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char *layerName: validationLayers) {
        bool layerFound = false;

        for (const auto &layerProperties: availableLayers) {
            if (strcmp(layerProperties.layerName, layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            spdlog::warn("Could not find validation layer: " + std::string(layerName));
            return false;
        }
    }

    return true;
}

class TriangleApp {
public:
    void run() {
        initVindow();
        initVulkan();
        mainLoop();
        cleanup();
    };
private:
    GLFWwindow *window;
    VkInstance instance;

    void initVindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "window", nullptr, nullptr);
    }

    void initVulkan() {
        createInstance();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void createInstance() {
        auto valLayersFmt = strVecFormat(validationLayers);
        if (enableValidationLayers) {
            if (!checkValidationLayerSupport()) {
                throw std::runtime_error("validation layers requested but not available");
            } else { spdlog::info("Validation layers  found: " + valLayersFmt); }
        } else { spdlog::info("Skp validation layer check"); }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "basic";
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
        appInfo.pEngineName = "no engine";
        appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &instance)) {
            throw std::runtime_error("failed to create instance!");
        }
    }
};

int main() {
    TriangleApp app;
    try {
        app.run();
    } catch (const std::exception &e) {
        spdlog::error(e.what());
        return EXIT_FAILURE;
    }

    spdlog::info("Exit program");
    return EXIT_SUCCESS;
}