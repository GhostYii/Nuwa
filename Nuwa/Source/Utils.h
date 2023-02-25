#pragma once
#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace Nuwa
{
	void GLClearError();
	bool GLFuncCheckError(const char* func, const char* file, int line);

	void TryCreateDefaultEngineConfig(const std::string& path);
	void ReadGlobalValuesByConfig(const std::string& path);

	float GetScreenAspect();
}
