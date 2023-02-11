#include "MeshRenderer.h"
#include "../Graphics/VertexArray.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"

namespace Nuwa
{
	MeshRenderer::MeshRenderer()
		: renderer(ToyRenderer())
	{
	}

	void MeshRenderer::SetMesh(Mesh* mesh, const std::string& shaderPath, const std::string& texturePath)
	{
		this->mesh = std::make_shared<Mesh>(mesh);

		GL_ASSERT(glEnable(GL_BLEND));
		GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		vao = std::make_unique<VertexArray>();
		vbo = std::make_unique<VertexBuffer>(mesh->GetVertices(), mesh->GetVerticesSize());

		VertexLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);

		vao->AddBuffer(*vbo, layout);

		ibo = std::make_unique<IndexBuffer>(mesh->GetIndices(), mesh->GetIndicesSize());

		// TODO: 验证文件是否存在
		if (shaderPath != "")
		{
			shader = std::make_unique<Shader>(shaderPath);
			shader->Bind();
			shader->SetInt("tex", 0);
		}
		// TODO: 验证文件是否存在
		if (texturePath != "")
			texture = std::make_unique<Texture>(texturePath);
	}

	void MeshRenderer::Draw()
	{
		if (!mesh)
			return;

		if (texture)
			texture->Bind();		

		// TODO: draw to camera
	}
}
