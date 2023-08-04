#include "vk_instance.h"

#include <algorithm>
#include <cstring>
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

	// Validation layers.
	if (c_enableValidationLayers && !HasValidationLayerSupport()) {
		Logger::Instance().Error("Requested validation layers are not available.");
	}
	if (c_enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(c_validationLayers.size());
		createInfo.ppEnabledLayerNames = c_validationLayers.data();
	} else {
		createInfo.enabledLayerCount = 0;
	}

	// Create instance.
	VkAssert(vkCreateInstance(&createInfo, nullptr, &m_instance),
		"Failed to create instance.");
}

void Vk_Instance::Destroy() {
	vkDestroyInstance(m_instance, nullptr);
}

void Vk_Instance::InitializeValidationLayer() {
}

bool Vk_Instance::HasValidationLayerSupport() {
	// Get available layers.
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	// Check if all validation layers are available.
	for (const char* i : c_validationLayers) {
		bool found = std::find_if(availableLayers.begin(), availableLayers.end(),
			[&i](VkLayerProperties prop) -> bool {
				return strcmp(i, prop.layerName) == 0;
			}
		) != availableLayers.end();

		if (!found) {
			return false;
		}
	}

	return true;
}

}
