#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Silicon {

class Window {
public:
	struct ExtensionInfo {
		uint32_t count;
		const char** names;
	};

	void* GetWindowHandle() { return m_windowHandle; }

	ExtensionInfo GetExtensionInfo();

	void Initialize();

	void Destroy();

	bool ShouldClose();

	void PollEvents();

	VkResult CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surfacePtr);

private:
	GLFWwindow* m_windowHandle;
};

}
