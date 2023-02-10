#pragma once
#include "Utils.h"

#define ASSERT(x) if (!(x)) __debugbreak();

#define GL_ASSERT(x) do \
{\
	Nuwa::GLClearError();\
	x;\
	ASSERT(Nuwa::GLFuncCheckError(#x, __FILE__, __LINE__));\
} while (0)

#define BPP_COUNT_RGBA 4