#include "MeshRenderer.h"
#include "../Transform.h"
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
		this->mesh = std::make_shared<Mesh>(*mesh);

		GL_ASSERT(glEnable(GL_BLEND));
		GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		vao = std::make_unique<VertexArray>();
		vbo = std::make_unique<VertexBuffer>(mesh->GetVertices().data(), mesh->GetVerticesSize());

		VertexLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);

		vao->AddBuffer(*vbo, layout);

		ibo = std::make_unique<IndexBuffer>(mesh->GetIndices().data(), mesh->GetIndicesSize());

		// TODO: ��֤�ļ��Ƿ����
		if (shaderPath != "")
		{
			shader = std::make_unique<Shader>(shaderPath);
			shader->Bind();
			shader->SetInt("tex", 0);
		}
		// TODO: ��֤�ļ��Ƿ����
		if (texturePath != "")
		{
			texture = std::make_unique<Texture>(texturePath);
		}
	}

	void MeshRenderer::Draw(const Camera& camera)
	{
		if (!mesh)
			return;

		if (texture)
			texture->Bind();

		shader->Bind();
		//shader->SetMatrix4x4("cameraMatrix", camera.GetMatrix());

		Matrix4x4 mvp = camera.GetProjectMatrix() * camera.GetViewMatrix() * transform->GetModelMatrix();		
		shader->SetMatrix4x4("mvp", mvp);

		vao->Bind();
		ibo->Bind();

		GL_ASSERT(glDrawElements(GL_TRIANGLES, ibo->Count(), GL_UNSIGNED_INT, nullptr));
	}
}
