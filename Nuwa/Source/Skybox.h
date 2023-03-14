#pragma once
#include <vector>
#include <string>
#include "EngineTypes.h"

namespace Nuwa
{
	class VertexArray;
	class IndexBuffer;
	class Shader;
	class CubeMap;

	class Skybox
	{
	public:
		Skybox();
		Skybox(std::string path);
		~Skybox();

		void Draw();

	private:
		std::string filename;

		VertexArray* vao;		
		IndexBuffer* ibo;
		Shader* shader;
		CubeMap* cubemap;

	private:
		static std::vector<float> vertices;
		static std::vector<uint> indices;

	private:
		void Create();
	};
}
