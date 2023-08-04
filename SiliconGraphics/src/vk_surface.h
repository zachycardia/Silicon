#pragma once

#include <functional>
#include <vulkan/vulkan.h>

namespace Silicon {

class Vk_Surface {

public:

	VkSurfaceKHR Handle() const { return m_surface; }

	struct CreateInfo {
		VkInstance instance;
		std::function<VkResult(VkInstance, VkSurfaceKHR*)> surfaceCreationFunc;
	};

	void Initialize(CreateInfo info);

	void Destroy(VkInstance instance);

private:

	VkSurfaceKHR m_surface;

};

}
