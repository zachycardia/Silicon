#include "vk_device.h"

#include <vector>

#include "common/vulkan_assert.h"
#include "logging/logger.h"

namespace Silicon {

void Vk_Device::Initialize(VkInstance instance) {
	InitializePhysicalDevice(instance);
	InitializeLogicalDevice(instance);
}

void Vk_Device::Destroy() {
	vkDestroyDevice(m_device, nullptr);
}

void Vk_Device::InitializePhysicalDevice(VkInstance instance) {
	uint32_t deviceCount{0};
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		Logger::Instance().Fatal("No devices with Vulkan support found.");
	}

	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data());

	m_physicalDevice = VK_NULL_HANDLE;

	for (const VkPhysicalDevice& device : physicalDevices) {
		if (IsDeviceSuitable(device)) {
			m_physicalDevice = device;
			break;
		}
	}

	if (m_physicalDevice == VK_NULL_HANDLE) {
		Logger::Instance().Fatal("No suitable devices found.");
	}
}

bool Vk_Device::IsDeviceSuitable(VkPhysicalDevice device) {
	VkPhysicalDeviceProperties properties;
	vkGetPhysicalDeviceProperties(device, &properties);

	VkPhysicalDeviceFeatures features;
	vkGetPhysicalDeviceFeatures(device, &features);

	QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(device);

	bool result = queueFamilyIndices.IsComplete();

	return result;
}

Vk_Device::QueueFamilyIndices Vk_Device::FindQueueFamilies(VkPhysicalDevice device) {
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount{0};
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i{0};
	for (const VkQueueFamilyProperties& props : queueFamilies) {
		// Graphics
		if (props.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		if (indices.IsComplete()) {
			break;
		}

		++i;
	}

	return indices;
}

void Vk_Device::InitializeLogicalDevice(VkInstance instance) {
	QueueFamilyIndices indices = FindQueueFamilies(m_physicalDevice);

	float queuePriority = 1.0f;

	VkDeviceQueueCreateInfo deviceQueueCreateInfo{
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.queueFamilyIndex = indices.graphicsFamily.value(),
		.queueCount = 1,
		.pQueuePriorities = &queuePriority
	};

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo deviceCreateInfo{
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &deviceQueueCreateInfo,
		.enabledExtensionCount = 0,
		.pEnabledFeatures = &deviceFeatures,
	};

	VkAssert(vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_device),
		"Failed to create device.");
}

void Vk_Device::InitializeQueues() {
	QueueFamilyIndices indices = FindQueueFamilies(m_physicalDevice);

	vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
}
	
}
