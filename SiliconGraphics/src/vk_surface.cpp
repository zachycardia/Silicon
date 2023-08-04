#include "vk_surface.h"

#include <vulkan/vulkan.h>

#include "common/vulkan_assert.h"

namespace Silicon {

void Vk_Surface::Initialize(CreateInfo info) {
	VkAssert(info.surfaceCreationFunc(info.instance, &m_surface),
		"Failed to create surface.");
}

void Vk_Surface::Destroy(VkInstance instance) {
	vkDestroySurfaceKHR(instance, m_surface, nullptr);
}

}
