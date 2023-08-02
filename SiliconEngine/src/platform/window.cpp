#include "window.h"

#include "logging/logger.h"

namespace Silicon {

void Window::Initialize() {
	// Initialize GLFW.
	if (!glfwInit()) {
		//TODO Error.
		Logger::Instance().Fatal("Unable to initialize GLFW.");
		return;
	}

	// Create window.
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_windowHandle = glfwCreateWindow(800, 600,
		"Silicon Engine",
		nullptr, nullptr);
}

void Window::Destroy() {
	glfwDestroyWindow(m_windowHandle);
	glfwTerminate();
}

bool Window::ShouldClose() {
	return glfwWindowShouldClose(m_windowHandle);
}

void Window::PollEvents() {
	glfwPollEvents();
}

}
