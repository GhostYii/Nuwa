#pragma once
#include <GL/glew.h>
#include "../EngineTypes.h"

namespace Nuwa
{
	class VertexArray;
	class IndexBuffer;
	class Shader;

	class ToyRenderer
	{
	public:
		static void Draw(VertexArray* vao, IndexBuffer* ibo, Shader* shader);
		static void Clear();
	};
}

