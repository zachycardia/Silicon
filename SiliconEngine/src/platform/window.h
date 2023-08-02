#pragma once

#include <GLFW/glfw3.h>

namespace Silicon {

class Window {
public:
	void Initialize();

	void Destroy();

	bool ShouldClose();

	void PollEvents();

private:
	GLFWwindow* m_window;
};

}
