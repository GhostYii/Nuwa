#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(int argc, char** argv)
{
	GLFWwindow* window = nullptr;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1366, 768, "Nuwa Framework", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "glew init failed." << std::endl;	

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}