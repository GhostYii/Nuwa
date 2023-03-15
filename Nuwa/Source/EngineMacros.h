#pragma once
#ifdef NUWA_EXPORT
#define NUWA_API __declspec(dllexport)
#else
#define NUWA_API __declspec(dllimport)
#endif

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

#define UB_NAME_CAM_MAT "CameraMatrix"
// uniform binding point - camera matrix
#define UB_POINT_CAM_MAT 0

#define CFG_SECTION_WINDOW "WINDOW"
#define CFG_WIDTH "width"
#define CFG_HEIGHT "height"
#define CFG_FULLSCREEN "is_fullscreen"

#define CFG_SECTION_LIGHT "LIGHT"
#define CFG_AMBIENT_COLOR "ambient_color"
#define CFG_DIFFUSE_COLOR "diffuse_color"
#define CFG_SPECULAR_COLOR "specular_color"

