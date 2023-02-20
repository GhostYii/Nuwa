#include "ToyRenderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "../EngineMacros.h"

void Nuwa::ToyRenderer::Draw(Nuwa::VertexArray* vao, Nuwa::IndexBuffer* ibo, Nuwa::Shader* shader) const
{
	shader->Bind();
	vao->Bind();
	ibo->Bind();

	GL_ASSERT(glDrawElements(GL_TRIANGLES, ibo->Count(), GL_UNSIGNED_INT, nullptr));
}

void Nuwa::ToyRenderer::Clear() const
{
	GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
