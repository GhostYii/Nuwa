#pragma once
#include <GL/glew.h>
#include "../EngineTypes.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace Nuwa
{
	class ToyRenderer
	{
	public:		
		void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
		void Clear() const;
	};
}

