
#include "renderer.h"

#ifdef _DEBUG
	#define DBG(x) std::cout << x << std::endl;
#else
	#define DBG(x)
#endif

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	GLFWwindow* window = Renderer::create_window();

	if (!Renderer::init(window))
	{
		return -1;
	}

	Renderer::create_buffers();
	Renderer::create_shaders();
	
	while (glfwWindowShouldClose(window) == false)
	{
		process_input(window);

		Renderer::draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Renderer::shutdown(window);

	return 0;
}