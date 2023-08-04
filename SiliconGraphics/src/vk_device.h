#pragma once

#include <optional>
#include <vulkan/vulkan.h>

namespace Silicon {

class Vk_Device {

public:

	void Initialize(VkInstance instance, VkSurfaceKHR surface);

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
	VkQueue m_presentQueue;

	void InitializePhysicalDevice(VkInstance instance, VkSurfaceKHR surface);

	bool IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

	void InitializeLogicalDevice(VkInstance instance, VkSurfaceKHR surface);

	void InitializeQueues(VkSurfaceKHR surface);

};

}
