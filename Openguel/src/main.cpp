
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#ifdef _DEBUG
	#define DBG(x) std::cout << x << std::endl;
#else
	#define DBG(x)
#endif

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

const char* vertex_shader_source = "#version 330 core\n"
	"layout (location = 0) in vec3 inPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);\n"
	"}";

const char* fragment_shader_source = "#version 330 core\n"
	"out vec4 FragColor;"
	"void main()"
	"{"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
	"}";

void window_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	GLFWwindow* window = nullptr;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(480, 360, "OpenGUEL", nullptr, nullptr);

	if (window == nullptr)
	{
		DBG("Failed to create Window.")
			glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
	{
		DBG("Failed to load GLAD.")
			return -1;
	}

	glViewport(0, 0, 480, 360);

	glfwSetFramebufferSizeCallback(window, window_resize_callback);

	unsigned int vertex_buffer;
	glGenBuffers(1, &vertex_buffer);

	unsigned int vertex_array;
	glGenVertexArrays(1, &vertex_array);

	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
	glCompileShader(vertex_shader);

	int success = 0;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		return -1;
	}

	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		return -1;
	}

	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	
	if (!success)
	{
		return -1;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);


	while (glfwWindowShouldClose(window) == false)
	{
		process_input(window);

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vertex_array);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glUseProgram(shader_program);
		glBindVertexArray(vertex_buffer);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}