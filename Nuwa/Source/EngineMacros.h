#pragma once
#include "Utils.h"

#define ASSERT(x) if (!(x)) __debugbreak();

#define GL_ASSERT(x) do \
{\
	Nuwa::GLClearError();\
	x;\
	ASSERT(Nuwa::GLFuncCheckError(#x, __FILE__, __LINE__));\
} while (0)

#define MAX_TEXTURE_COUNT 16

#define ALBEDO_MAP_INDEX 0
#define SPECULAR_MAP_INDEX 1
#define NORMAL_MAP_INDEX 2
#define EMISSION_MAP_INDEX 3

//#define BPP_COUNT_RGBA 4

#define CFG_SECTION_WINDOW "WINDOW"
#define CFG_WIDTH "width"
#define CFG_HEIGHT "height"
#define CFG_FULLSCREEN "is_fullscreen"

#define CFG_SECTION_LIGHT "LIGHT"
#define CFG_AMBIENT_COLOR "ambient_color"
#define CFG_DIFFUSE_COLOR "diffuse_color"
#define CFG_SPECULAR_COLOR "specular_color"

