/**
 * @file    SiliconEngine.cpp
 *
 * @brief   Engine class.
 *
 * @author  Zachary Ning
**/

#include "silicon_engine.h"
#include "silicon_graphics.h"
#include "logging/logger.h"

namespace Silicon {

void Engine::Initialize() {
	// Logger
	Logger::Singleton_Initialize();

	Logger::Instance().Trace("Initializing engine.");

	// Platform
	m_window.Initialize();

	// Graphics
	Graphics::Singleton_Initialize();
	Window::ExtensionInfo extensionInfo = m_window.GetExtensionInfo();
	Graphics::Instance().Initialize(Graphics::InitializeInfo{
		.windowHandle = m_window.GetWindowHandle(),
		.extensionCount = extensionInfo.count,
		.extensionNames = extensionInfo.names
	});

	Logger::Instance().Trace("Engine initialized.");
}

void Engine::Destroy() {
	Logger::Instance().Trace("Destroying engine.");

	// Graphics
	Graphics::Instance().Destroy();
	Graphics::Singleton_Reset();

	// Platform
	m_window.Destroy();

	Logger::Instance().Trace("Engine destroyed.");

	// Logger
	Logger::Singleton_Reset();
}

void Engine::Run() {
	while (!m_window.ShouldClose()) {
		m_window.PollEvents();
	}
}

}
