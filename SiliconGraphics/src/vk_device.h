#pragma once

#include <optional>
#include <vulkan/vulkan.h>

namespace Silicon {

class Vk_Device {

public:

	void Initialize(VkInstance instance);

	void Destroy();

private:

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool IsComplete() {
			return graphicsFamily.has_value() &&
				presentFamily.has_value();
		}
	};

	VkPhysicalDevice m_physicalDevice;
	VkDevice m_device;
	VkQueue m_graphicsQueue;

	void InitializePhysicalDevice(VkInstance instance);

	bool IsDeviceSuitable(VkPhysicalDevice device);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	void InitializeLogicalDevice(VkInstance instance);

	void InitializeQueues();

};

}
