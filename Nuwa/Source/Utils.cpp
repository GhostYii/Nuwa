#include "Utils.h"

void Nuwa::GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool Nuwa::GLFuncCheckError(const char* func, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
        std::string errorStr = "UNKNOW_ERROR";
        switch (error)
        {
        case GL_INVALID_ENUM:                  errorStr = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 errorStr = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             errorStr = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                errorStr = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               errorStr = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 errorStr = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: errorStr = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
		spdlog::error("[OpenGL Error] - {}({}): {} {}:line{}", errorStr, error, func, file, line);
		return false;
	}
	return true;
}