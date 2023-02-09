#pragma once
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
}