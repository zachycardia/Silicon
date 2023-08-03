#include "vk_instance.h"

#include <vector>
#include <vulkan/vulkan.h>

#include "common/vulkan_assert.h"
#include "logging/logger.h"

namespace Silicon {

void Vk_Instance::Create(InstanceCreateInfo info) {
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
		.enabledExtensionCount = info.extensionCount,
		.ppEnabledExtensionNames = info.extensionNames
	};

	VkAssert(vkCreateInstance(&createInfo, nullptr, &m_instance),
		"Failed to create instance.");
}

void Vk_Instance::Destroy() {
	vkDestroyInstance(m_instance, nullptr);
}

}
