#pragma once

#include "singleton.h"

#include <functional>

#include "vk_device.h"
#include "vk_instance.h"
#include "vk_surface.h"

namespace Silicon {

class Graphics : public Singleton<Graphics> {

public:

	struct InitializeInfo {
		void* windowHandle;
		uint32_t extensionCount;
		const char** extensionNames;
		std::function<VkResult(VkInstance, VkSurfaceKHR*)> surfaceCreationFunc;
	};

	void Initialize(InitializeInfo info);

	void Destroy();

private:

	void* m_windowHandle;

	Vk_Instance m_instance;
	Vk_Surface m_surface;
	Vk_Device m_device;

};

}
