#include "ToyRenderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "../EngineMacros.h"

namespace Nuwa
{
	void ToyRenderer::Draw(VertexArray* vao, IndexBuffer* ibo, Shader* shader)
	{
		shader->Bind();
		vao->Bind();
		ibo->Bind();

		GL_ASSERT(glDrawElements(GL_TRIANGLES, ibo->Count(), GL_UNSIGNED_INT, nullptr));

		shader->Unbind();
		vao->Unbind();
		ibo->Unbind();
	}

	void ToyRenderer::Clear()
	{
		GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}
}