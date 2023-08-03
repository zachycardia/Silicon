#pragma once

#include "singleton.h"

#include "vk_instance.h"

namespace Silicon {

class Graphics : public Singleton<Graphics> {

public:

	struct InitializeInfo {
		void* windowHandle;
		uint32_t extensionCount;
		const char** extensionNames;
	};

	void Initialize(InitializeInfo info);

	void Destroy();

private:

	void* m_windowHandle;

	Vk_Instance m_instance;

};

}
