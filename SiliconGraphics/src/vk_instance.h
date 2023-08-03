#pragma once

#include <vulkan/vulkan.h>

namespace Silicon {

class Vk_Instance {

public:

	struct InstanceCreateInfo {
		uint32_t extensionCount;
		const char** extensionNames;
	};

	void Create(InstanceCreateInfo info);

	void Destroy();

private:

	VkInstance m_instance;
};

}
