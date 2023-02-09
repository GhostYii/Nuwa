#pragma once
#include <string>
#include <GL/glew.h>

namespace Nuwa
{
	typedef unsigned int uint;
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef long long int64;

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
		//bool isNormalized;
		uchar normalized;

		static uint GetTypeSize(uint type)
		{
			switch (type)
			{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			}
			return 0;
		}
	};
}