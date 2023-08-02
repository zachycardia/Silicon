#include "silicon_graphics.h"

#include <vector>
#include <vulkan/vulkan.h>

#include "common/vulkan_assert.h"
#include "logging/logger.h"

namespace Silicon {

void Graphics::Initialize() {
	CreateInstance();
}

void Graphics::Destroy() {
	DestroyInstance();
}

void Graphics::SetWindowHandle(void* handle) {
	m_windowHandle = handle;
}

void Graphics::SetExtensionInfo(uint32_t count, const char** names) {
	m_extensionInfo.count = count;
	m_extensionInfo.names = names;
}

void Graphics::CreateInstance() {
	// Instance

	VkApplicationInfo appInfo{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "Silicon Engine",
		.applicationVersion = VK_MAKE_VERSION(0, 1, 0),
		.pEngineName = "Silicon Engine",
		.engineVersion = VK_MAKE_VERSION(0, 1, 0),
		.apiVersion = VK_API_VERSION_1_3
	};

	VkInstanceCreateInfo createInfo{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &appInfo,
		.enabledLayerCount = 0,
		.enabledExtensionCount = m_extensionInfo.count,
		.ppEnabledExtensionNames = m_extensionInfo.names
	};

	VkAssert(vkCreateInstance(&createInfo, nullptr, &m_instance),
		"Failed to create instance.");
}

void Graphics::DestroyInstance() {
	vkDestroyInstance(m_instance, nullptr);
}

}
