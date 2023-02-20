#include "MeshRenderer.h"
#include "../Transform.h"
#include "../Graphics/VertexArray.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"

#ifdef NUWA_EDITOR
#include "../Editor/EditorGUI.h"
#endif // NUWA_EDITOR


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
		layout.Push<float>(3);	//pos
		layout.Push<float>(2);	//uv
		layout.Push<float>(3);	//norm

		vao->AddBuffer(*vbo, layout);

		ibo = std::make_unique<IndexBuffer>(mesh->GetIndices().data(), mesh->GetIndicesSize());

		// TODO: 验证文件是否存在
		if (shaderPath != "")
		{
			shader = std::make_unique<Shader>(shaderPath);
			shader->Bind();
			shader->SetInt("tex", 0);
		}
		// TODO: 验证文件是否存在
		if (texturePath != "")
		{
			texture = std::make_unique<Texture>(texturePath);
		}
	}

	void MeshRenderer::Draw()
	{
		if (texture)
			texture->Bind();

		shader->Bind();
		//shader->SetMatrix4x4("cameraMatrix", camera.GetMatrix());

		Matrix4x4 mvp = drawCamera->GetProjectMatrix() * drawCamera->GetViewMatrix() * transform->GetModelMatrix();
		shader->SetMatrix4x4("mvp", mvp);

		vao->Bind();
		ibo->Bind();

		GL_ASSERT(glDrawElements(GL_TRIANGLES, ibo->Count(), GL_UNSIGNED_INT, nullptr));
	}

	void MeshRenderer::SetCamera(Camera* camera)
	{		
		drawCamera = std::shared_ptr<Camera>(camera);
	}

	void MeshRenderer::InternalRender()
	{
		if (!drawCamera || !mesh)
			return;

		Draw();
	}

	void MeshRenderer::OnInspectorGUI()
	{
		if (ImGui::CollapsingHeader("Mesh Information", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Indent();
			if (mesh->GetModelPath() != "")
				EditorGUI::DrawLabel("Model Path", mesh->GetModelPath());
			EditorGUI::DrawLabel("Vertex Size", std::to_string(mesh->GetVerticesSize()));
			//EditorGUI::DrawLabel("Index Size", std::to_string(mesh->GetIndicesSize()));
			ImGui::Unindent();
		}

		if (ImGui::CollapsingHeader("Material Information (temp)", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Indent();
			EditorGUI::DrawLabel("Shader", shader->Filepath());
			EditorGUI::DrawLabel("Texture", texture->Filepath());
			ImGui::Unindent();
		}
	}
}
