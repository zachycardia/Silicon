#pragma once

#include <vector>
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
	const std::vector<const char*> c_validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};
#ifdef NDEBUG
	static constexpr bool c_enableValidationLayers = false;
#else
	static constexpr bool c_enableValidationLayers = true;
#endif

	VkInstance m_instance;

	void InitializeValidationLayer();

	bool HasValidationLayerSupport();

};

}
