/**
 * @file    SiliconEngine.h
 *
 * @brief   Engine class.
 *
 * @author  Zachary Ning
**/

#pragma once

#include "platform/window.h"

namespace Silicon {

class Engine {
public:
	void Initialize();

	void Destroy();

	void Run();

private:
	Window m_window;
};

}
