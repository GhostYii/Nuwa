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
		void Draw(Nuwa::VertexArray* vao, Nuwa::IndexBuffer* ibo, Shader* shader) const;
		void Clear() const;
	};
}

