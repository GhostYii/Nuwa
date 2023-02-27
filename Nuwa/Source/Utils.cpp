#include "Utils.h"
#include <fstream>
#include <mINI/ini.h>
#include "Basic/INIConfig.h"
#include "EngineMacros.h"
#include "Global.h"

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

void Nuwa::TryCreateDefaultEngineConfig(const std::string& path)
{
	std::ifstream ifs(path.c_str());
	if (ifs.good())
		return;

	mINI::INIFile config(path);
	mINI::INIStructure ini;
	config.read(ini);

	ini[CFG_SECTION_WINDOW][CFG_SECTION_WIDTH] = "1366";
	ini[CFG_SECTION_WINDOW][CFG_SECTION_HEIGHT] = "768";
	ini[CFG_SECTION_WINDOW][CFG_SECTION_FULLSCREEN] = "false";

	config.generate(ini);
}

void Nuwa::ReadGlobalValuesByConfig(const std::string& path)
{
	std::ifstream ifs(path.c_str());
	if (!ifs.good())
		TryCreateDefaultEngineConfig(path);

	INIConfig config = INIConfig(path);

	Global::Resolution = Vector2Int(std::stoi(config[CFG_SECTION_WINDOW][CFG_SECTION_WIDTH]), std::stoi(config[CFG_SECTION_WINDOW][CFG_SECTION_HEIGHT]));
	Global::IsFullScreen = config[CFG_SECTION_WINDOW][CFG_SECTION_FULLSCREEN] == "true" ? true : false;
}

std::string Nuwa::GetAllText(const std::string& path)
{
	std::ifstream stream(path);
	std::stringstream ss;
	std::string line;
	while (getline(stream, line))	
		ss << line << std::endl;	

	return ss.str();
}

float Nuwa::GetScreenAspect()
{
	return Global::Resolution.x / 1.0f / std::max(Global::Resolution.y, 1);
}
