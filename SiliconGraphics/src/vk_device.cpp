#include "vk_device.h"

#include <set>
#include <vector>

#include "common/vulkan_assert.h"
#include "logging/logger.h"

namespace Silicon {

void Vk_Device::Initialize(VkInstance instance, VkSurfaceKHR surface) {
	InitializePhysicalDevice(instance, surface);
	InitializeLogicalDevice(instance, surface);
}

void Vk_Device::Destroy() {
	vkDestroyDevice(m_device, nullptr);
}

void Vk_Device::InitializePhysicalDevice(VkInstance instance, VkSurfaceKHR surface) {
	uint32_t deviceCount{0};
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		Logger::Instance().Fatal("No devices with Vulkan support found.");
	}

	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data());

	m_physicalDevice = VK_NULL_HANDLE;

	for (const VkPhysicalDevice& device : physicalDevices) {
		if (IsDeviceSuitable(device, surface)) {
			m_physicalDevice = device;
			break;
		}
	}

	if (m_physicalDevice == VK_NULL_HANDLE) {
		Logger::Instance().Fatal("No suitable devices found.");
	}
}

bool Vk_Device::IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
	VkPhysicalDeviceProperties properties;
	vkGetPhysicalDeviceProperties(device, &properties);

	VkPhysicalDeviceFeatures features;
	vkGetPhysicalDeviceFeatures(device, &features);

	QueueFamilyIndices queueFamilyIndices = FindQueueFamilies(device, surface);

	bool result = queueFamilyIndices.IsComplete();

	return result;
}

Vk_Device::QueueFamilyIndices Vk_Device::FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) {
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

		// Present
		VkBool32 presentSupport{false};
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
		if (presentSupport) {
			indices.presentFamily = i;
		}

		if (indices.IsComplete()) {
			break;
		}

		++i;
	}

	return indices;
}

void Vk_Device::InitializeLogicalDevice(VkInstance instance, VkSurfaceKHR surface) {
	QueueFamilyIndices indices = FindQueueFamilies(m_physicalDevice, surface);

	float queuePriority = 1.0f;

	std::set<uint32_t> queueFamilyIndices{
		indices.graphicsFamily.value(),
		indices.presentFamily.value()
	};

	std::vector<VkDeviceQueueCreateInfo> deviceQueueCreateInfos;
	for (uint32_t index : queueFamilyIndices) {
		deviceQueueCreateInfos.push_back(VkDeviceQueueCreateInfo{
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = index,
			.queueCount = 1,
			.pQueuePriorities = &queuePriority
		});
	}

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo deviceCreateInfo{
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.queueCreateInfoCount = static_cast<uint32_t>(deviceQueueCreateInfos.size()),
		.pQueueCreateInfos = deviceQueueCreateInfos.data(),
		.enabledExtensionCount = 0,
		.pEnabledFeatures = &deviceFeatures,
	};

	VkAssert(vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_device),
		"Failed to create device.");
}

void Vk_Device::InitializeQueues(VkSurfaceKHR surface) {
	QueueFamilyIndices indices = FindQueueFamilies(m_physicalDevice, surface);

	vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
	vkGetDeviceQueue(m_device, indices.presentFamily.value(), 0, &m_presentQueue);
}
	
}
