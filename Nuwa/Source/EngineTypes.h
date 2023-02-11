#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Nuwa
{
	typedef unsigned int uint;
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef long long int64;
	typedef unsigned long long uint64;

	//typedef glm::vec4 Color;
	typedef glm::vec4 Vector4;
	typedef glm::vec3 Vector3;
	typedef glm::vec2 Vector2;
	typedef glm::mat3x3 Matrix3x3;
	typedef glm::mat4x4 Matrix4x4;

	typedef glm::quat Quaternion;

	struct ShaderSource
	{
		std::string vertex;
		std::string fragment;
	};

	enum class ShaderType
	{
		None = -1,
		Vertex,
		Fragment
	};

	struct VertexElement
	{
		uint type;
		uint count;
		uchar normalized;

		static uint GetTypeSize(uint type)
		{
			switch (type)
			{
			case GL_FLOAT: return sizeof(float);
			case GL_UNSIGNED_INT: return sizeof(uint);
			case GL_UNSIGNED_BYTE: return sizeof(uchar);
			}
			return 0;
		}
	};
}