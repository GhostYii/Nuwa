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

#define CFG_SECTION_WINDOW "WINDOW"
#define CFG_SECTION_WIDTH "Width"
#define CFG_SECTION_HEIGHT "Height"
#define CFG_SECTION_FULLSCREEN "IsFullScreen"