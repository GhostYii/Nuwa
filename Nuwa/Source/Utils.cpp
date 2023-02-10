#include "Utils.h"

void Nuwa::GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool Nuwa::GLFuncCheckError(const char* func, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		spdlog::error("[OpenGL Error] - {}: {} {}:line{}", error, func, file, line);
		return false;
	}
	return true;
}