#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include <spdlog/spdlog.h>
#include <glm/gtc/type_ptr.hpp>

#include "../EngineMacros.h"

Nuwa::Shader::Shader(const std::string& filepath)
	: filepath(filepath)
{
	auto source = Parse();
	rendererID = CreateShader(source.vertex, source.fragment);
}

Nuwa::Shader::~Shader()
{
	GL_ASSERT(glDeleteProgram(rendererID));
}

void Nuwa::Shader::SetInt(const std::string& name, int value)
{
	GL_ASSERT(glUniform1i(GetUniformLocation(name), value));
}

void Nuwa::Shader::SetColor(const std::string& name, Vector4 color)
{
	GL_ASSERT(glUniform4f(GetUniformLocation(name), color.r, color.g, color.b, color.a));
}

void Nuwa::Shader::SetMatrix4x4(const std::string& name, Matrix4x4 mat)
{
	GL_ASSERT(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
}

void Nuwa::Shader::Bind() const
{
	GL_ASSERT(glUseProgram(rendererID));
}

void Nuwa::Shader::Unbind() const
{
	GL_ASSERT(glUseProgram(NULL));
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
		if (line.find("$Subshader") != std::string::npos)
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
	uint program;
	GL_ASSERT(program = glCreateProgram());
	uint vs = Compile(GL_VERTEX_SHADER, vertex);
	uint fs = Compile(GL_FRAGMENT_SHADER, fragment);

	GL_ASSERT(glAttachShader(program, vs));
	GL_ASSERT(glAttachShader(program, fs));

	GL_ASSERT(glLinkProgram(program));
	GL_ASSERT(glValidateProgram(program));

	GL_ASSERT(glDeleteShader(vs));
	GL_ASSERT(glDeleteShader(fs));

	return program;
}

Nuwa::uint Nuwa::Shader::Compile(uint type, const std::string& source)
{
	uint id;
	GL_ASSERT(id = glCreateShader(type));
	const char* src = source.c_str();
	GL_ASSERT(glShaderSource(id, 1, &src, nullptr));
	GL_ASSERT(glCompileShader(id));

	int complieStatus;
	GL_ASSERT(glGetShaderiv(id, GL_COMPILE_STATUS, &complieStatus));
	if (complieStatus == GL_FALSE)
	{
		int length;
		GL_ASSERT(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* msg = (char*)_malloca(length * sizeof(char));

		GL_ASSERT(glGetShaderInfoLog(id, length, &length, msg));

		spdlog::error("Compile {} shader error: {}.\n", type, msg);
		GL_ASSERT(glDeleteShader(id));
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
