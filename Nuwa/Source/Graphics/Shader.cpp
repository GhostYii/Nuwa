#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include <spdlog/spdlog.h>

Nuwa::Shader::Shader(const std::string& filepath)
	: filepath(filepath)
{
	auto source = Parse();
	rendererID = CreateShader(source.vertex, source.fragment);
}

Nuwa::Shader::~Shader()
{
	glDeleteProgram(rendererID);
}

void Nuwa::Shader::Bind() const
{
	glUseProgram(rendererID);
}

void Nuwa::Shader::Unbind() const
{
	glUseProgram(NULL);
}

Nuwa::ShaderSource Nuwa::Shader::Parse()
{
	std::ifstream stream(filepath);
	ShaderSource source;
	ShaderType stype = ShaderType::None;

	std::stringstream ss[2];
	std::string line;
	while (getline(stream, line))
	{
		if (line.find("%Subshader") != std::string::npos)
		{
			if (line.find("Vertex") != std::string::npos)
				stype = ShaderType::Vertex;
			else if (line.find("Fragment") != std::string::npos)
				stype = ShaderType::Fragment;
		}
		else
		{
			if (stype == ShaderType::None)
				continue;

			ss[(int)stype] << line << std::endl;
		}
	}	

	return { ss[(int)ShaderType::Vertex].str(), ss[(int)ShaderType::Fragment].str() };
}

Nuwa::uint Nuwa::Shader::CreateShader(const std::string& vertex, const std::string& fragment)
{
	uint program = glCreateProgram();
	uint vs = Compile(GL_VERTEX_SHADER, vertex);
	uint fs = Compile(GL_FRAGMENT_SHADER, fragment);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

Nuwa::uint Nuwa::Shader::Compile(uint type, const std::string& source)
{
	uint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int complieStatus;
	glGetShaderiv(id, GL_COMPILE_STATUS, &complieStatus);
	if (complieStatus == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* msg = (char*)_malloca(length * sizeof(char));

		glGetShaderInfoLog(id, length, &length, msg);

		spdlog::error("Compile {} shader error: {}.\n", type, msg);
		glDeleteShader(id);
		return GL_FALSE;
	}

	return id;
}

int Nuwa::Shader::GetUniformLocation(const std::string& name) const
{
	if (uniformLocationMap.count(name))
		return uniformLocationMap[name];

	int location = glGetUniformLocation(rendererID, name.c_str());
	if (location == -1)
		spdlog::warn("uniform {} doesnt exist.\n", name);

	uniformLocationMap[name] = location;
	return location;
}
