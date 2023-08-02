#include "silicon_graphics.h"

#include <vulkan/vulkan.h>

#include "logging/logger.h"

namespace Silicon {

void Graphics::Initialize() {
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	Logger::Instance().Debug("Extensions: {0}", extensionCount);
}

void Graphics::Destroy() {

}

void Graphics::SetWindowHandle(void* handle) {
	m_windowHandle = handle;
}

}
