#pragma once

// C++ includes
#include <iostream>

// external
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef _DEBUG
#define DBG(x) std::cout << x << std::endl;
#else
#define DBG(x)
#endif

#define internal static

namespace Renderer
{
	GLFWwindow* create_window();

	bool init(GLFWwindow* window);

	bool create_buffers();

	bool create_shaders();

	void draw();

	void shutdown(GLFWwindow* window);
}