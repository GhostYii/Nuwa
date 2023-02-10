#include "Renderer.h"

void Nuwa::ToyRenderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
	shader.Bind();
	vao.Bind();
	ibo.Bind();

	glDrawElements(GL_TRIANGLES, ibo.Count(), GL_UNSIGNED_INT, nullptr);
}

void Nuwa::ToyRenderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
