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

	ini[CFG_SECTION_WINDOW][CFG_WIDTH] = "1366";
	ini[CFG_SECTION_WINDOW][CFG_HEIGHT] = "768";
	ini[CFG_SECTION_WINDOW][CFG_FULLSCREEN] = "false";

	ini[CFG_SECTION_LIGHT][CFG_AMBIENT_COLOR] = "0.05, 0.05, 0.05";
	ini[CFG_SECTION_LIGHT][CFG_DIFFUSE_COLOR] = "0.8, 0.8, 0.8";
	ini[CFG_SECTION_LIGHT][CFG_SPECULAR_COLOR] = "1.0, 1.0, 1.0";

	config.generate(ini);
}

void Nuwa::ReadGlobalValuesByConfig(const std::string& path)
{
	std::ifstream ifs(path.c_str());
	if (!ifs.good())
		TryCreateDefaultEngineConfig(path);

	INIConfig config = INIConfig(path);

	// WINDOW section
	{
		Global::Resolution = Vector2Int(std::stoi(config[CFG_SECTION_WINDOW][CFG_WIDTH]), std::stoi(config[CFG_SECTION_WINDOW][CFG_HEIGHT]));
		Global::IsFullScreen = config[CFG_SECTION_WINDOW][CFG_FULLSCREEN] == "true" ? true : false;
	}
	// LIGHT section
	{
		auto ambient = SplitString(config[CFG_SECTION_LIGHT][CFG_AMBIENT_COLOR], ',');
		if (ambient.size() == 3)
			Global::AmbientColor = { std::stof(trim(ambient[0])), std::stof(trim(ambient[1])), std::stof(trim(ambient[2])) };
		auto diffuse = SplitString(config[CFG_SECTION_LIGHT][CFG_DIFFUSE_COLOR], ',');
		if (diffuse.size() == 3)
			Global::DiffuseColor = { std::stof(trim(diffuse[0])), std::stof(trim(diffuse[1])), std::stof(trim(diffuse[2])) };
		auto specular = SplitString(config[CFG_SECTION_LIGHT][CFG_SPECULAR_COLOR], ',');
		if (specular.size() == 3)
			Global::SpecularColor = { std::stof(trim(specular[0])), std::stof(trim(specular[1])), std::stof(trim(specular[2])) };
	}

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

std::vector<std::string> Nuwa::SplitString(std::string str, std::string delimiter)
{
	size_t beg = 0, end, len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((end = str.find(delimiter, beg)) != std::string::npos) 
	{
		token = str.substr(beg, end - beg);
		beg = end + len;
		res.push_back(token);
	}

	res.push_back(str.substr(beg));
	return res;
}

std::vector<std::string> Nuwa::SplitString(const std::string& str, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string item;

	while (getline(ss, item, delim)) 	
		result.push_back(item);	

	return result;
}

std::string& Nuwa::ltrim(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

std::string& Nuwa::rtrim(std::string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

std::string& Nuwa::trim(std::string& s)
{
	return ltrim(rtrim(s));
}

float Nuwa::GetScreenAspect()
{
	return Global::Resolution.x / 1.0f / std::max(Global::Resolution.y, 1);
}
