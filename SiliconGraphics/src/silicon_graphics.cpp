#include "silicon_graphics.h"

#include <vector>
#include <vulkan/vulkan.h>

#include "common/vulkan_assert.h"
#include "logging/logger.h"

namespace Silicon {

void Graphics::Initialize(InitializeInfo info) {
	m_windowHandle = info.windowHandle;

	// Initialize instance.
	m_instance.Create(Vk_Instance::InstanceCreateInfo{
		.extensionCount = info.extensionCount,
		.extensionNames = info.extensionNames
	});

	// Initialize device.
	m_device.Initialize(m_instance.Handle());
}

void Graphics::Destroy() {
	m_device.Destroy();
	m_surface.Destroy();
	m_instance.Destroy();
}

}
