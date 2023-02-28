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

	std::string GetAllText(const std::string& path);
	std::vector<std::string> SplitString(std::string str, std::string delimiter);
	std::vector<std::string> SplitString(const std::string& str, char delim);

	std::string& ltrim(std::string& s);	
	std::string& rtrim(std::string& s);
	std::string& trim(std::string& s);

	float GetScreenAspect();
}
