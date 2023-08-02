#pragma once

#include "singleton.h"

namespace Silicon {

class Graphics : public Singleton<Graphics> {
public:
	void Initialize();

	void Destroy();

	void SetWindowHandle(void* handle);

private:
	void* m_windowHandle;
};

}
