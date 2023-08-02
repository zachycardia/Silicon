#pragma once

#include "singleton.h"

#include <vulkan/vulkan.h>

namespace Silicon {

class Graphics : public Singleton<Graphics> {
public:
	void Initialize();

	void Destroy();

	void SetWindowHandle(void* handle);

	void SetExtensionInfo(uint32_t count, const char** names);

private:
	struct ExtensionInfo {
		uint32_t count;
		const char** names;
	};

	void* m_windowHandle;

	VkInstance m_instance;

	ExtensionInfo m_extensionInfo;

	void CreateInstance();

	void DestroyInstance();
};

}
