#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include <spdlog/spdlog.h>
#include <glm/gtc/type_ptr.hpp>

#include "../EngineMacros.h"

namespace Nuwa
{
	Shader::Shader(const std::string& filepath)
		: filepaths({ filepath })
	{
		auto source = Parse();
		rendererID = CreateShader(source.vertex, source.fragment);
	}

	Shader::Shader(const std::string& vertFilePath, const std::string& fragFilePath)
		: filepaths({ vertFilePath, fragFilePath })
	{
		rendererID = CreateShader(GetAllText(vertFilePath), GetAllText(fragFilePath));
	}

	Shader::~Shader()
	{
		GL_ASSERT(glDeleteProgram(rendererID));
	}

	void Shader::SetInt(const std::string& name, int value)
	{
		if (!HasUniform(name))
			return;

		Bind();
		GL_ASSERT(glUniform1i(GetUniformLocation(name), value));
	}

	void Shader::SetFloat(const std::string& name, float value)
	{
		if (!HasUniform(name))
			return;

		Bind();
		GL_ASSERT(glUniform1f(GetUniformLocation(name), value));
	}

	void Shader::SetVector3(const std::string& name, Vector3 value)
	{
		if (!HasUniform(name))
			return;

		Bind();
		GL_ASSERT(glUniform3f(GetUniformLocation(name), value.x, value.y, value.z));
	}

	void Shader::SetColor(const std::string& name, Vector4 color)
	{
		if (!HasUniform(name))
			return;

		Bind();
		GL_ASSERT(glUniform4f(GetUniformLocation(name), color.r, color.g, color.b, color.a));
	}

	void Shader::SetColor(const std::string& name, Vector3 color)
	{
		if (!HasUniform(name))
			return;

		Bind();
		GL_ASSERT(glUniform3f(GetUniformLocation(name), color.x, color.y, color.z));
	}

	void Shader::SetMatrix4x4(const std::string& name, Matrix4x4 mat)
	{
		if (!HasUniform(name))
			return;

		Bind();
		GL_ASSERT(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
	}

	int Shader::GetInt(const std::string& name) const
	{
		int loc = GetUniformLocation(name);
		if (loc == -1)
			return 0;

		int value = 0;
		GL_ASSERT(glGetUniformiv(rendererID, loc, &value));
		return value;
	}

	Vector3 Shader::GetColor(const std::string& name) const
	{
		int loc = GetUniformLocation(name);
		if (loc == -1)
			return Vector3(0);

		Vector3 color;
		GL_ASSERT(glGetUniformfv(rendererID, loc, glm::value_ptr(color)));
		return color;
	}

	bool Shader::HasUniform(const std::string& name)
	{
		if (uniformLocationMap.find(name) != uniformLocationMap.end())
			return true;

		int location = -1;
		GL_ASSERT(location = glGetUniformLocation(rendererID, name.c_str()));
		if (location == -1)
			return false;

		return true;
	}

	void Shader::Bind() const
	{
		GL_ASSERT(glUseProgram(rendererID));
	}

	void Shader::Unbind() const
	{
		GL_ASSERT(glUseProgram(NULL));
	}

	ShaderSource Shader::Parse()
	{
		std::ifstream stream(filepaths[0]);
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

	uint Shader::CreateShader(const std::string& vertex, const std::string& fragment)
	{
		uint program;
		GL_ASSERT(program = glCreateProgram());
		uint vs = Compile(GL_VERTEX_SHADER, vertex);
		uint fs = Compile(GL_FRAGMENT_SHADER, fragment);

		GL_ASSERT(glAttachShader(program, vs));
		GL_ASSERT(glAttachShader(program, fs));

		Link(program);
		Validate(program);

		GL_ASSERT(glDeleteShader(vs));
		GL_ASSERT(glDeleteShader(fs));

		return program;
	}

	uint Shader::Compile(uint type, const std::string& source)
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
			spdlog::error("Compile {} shader error: {}.", type, msg);
			delete[] msg;
			GL_ASSERT(glDeleteShader(id));
			return GL_FALSE;
		}

		return id;
	}

	void Shader::Link(uint program)
	{
		GL_ASSERT(glLinkProgram(program));
		GLint progStatus;
		glGetProgramiv(program, GL_LINK_STATUS, &progStatus);
		if (progStatus == GL_FALSE)
		{
			int length;
			GL_ASSERT(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
			char* msg = (char*)_malloca(length * sizeof(char));
			GL_ASSERT(glGetProgramInfoLog(program, length, &length, msg));
			spdlog::error("Shader Program Link error: {}", msg);
			delete[] msg;
			GL_ASSERT(glDeleteShader(program));
		}
	}

	void Shader::Validate(uint program)
	{
		GL_ASSERT(glValidateProgram(program));
		GLint progValidate;
		GL_ASSERT(glGetProgramiv(program, GL_VALIDATE_STATUS, &progValidate));
		if (progValidate == GL_FALSE)
		{
			int length;
			GL_ASSERT(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
			char* msg = (char*)_malloca(length * sizeof(char));
			GL_ASSERT(glGetProgramInfoLog(program, length, &length, msg));
			spdlog::error("Shader Program Validate error: {}", msg);
			delete[] msg;
			GL_ASSERT(glDeleteShader(program));
		}
	}

	int Shader::GetUniformLocation(const std::string& name) const
	{
		if (uniformLocationMap.find(name) != uniformLocationMap.end())
			return uniformLocationMap[name];

		int location = -1;
		GL_ASSERT(location = glGetUniformLocation(rendererID, name.c_str()));
		if (location == -1)
		{
			spdlog::warn("uniform {} doesnt exist.", name);
			return location;
		}

		uniformLocationMap[name] = location;
		return location;
	}
}

