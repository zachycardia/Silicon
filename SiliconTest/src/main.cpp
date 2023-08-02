/**
 * @file    main.cpp
 *
 * @brief   Program entry point.
 *          Used for debugging purposes.
 * 
 * @author  Zachary Ning
**/

#include "silicon_engine.h"

int main() {
	Silicon::Engine engine{};

	engine.Initialize();

	engine.Run();

	engine.Destroy();

	return 0;
}
