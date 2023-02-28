#include "MeshRenderer.h"
#include "../Transform.h"
#include "../Graphics/VertexArray.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Material.h"
#include "../Graphics/Texture.h"
#include "../Global.h"

#ifdef NUWA_EDITOR
#include "../Editor/EditorGUI.h"
#endif // NUWA_EDITOR


namespace Nuwa
{
	MeshRenderer::MeshRenderer()
	{
	}

	void MeshRenderer::SetMesh(Mesh* mesh, const std::string& shaderPath)
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
			material = std::make_shared<Material>(new Shader(shaderPath));
			material->SetAlbedoMap("Resources/Textures/nuwa.png");
			material->SetSpecularMap("Resources/Textures/nuwa.png");

			//material->SetUniformValue<int>("tex", 0);
			//material->SetUniformValue<float>("intensity", 1.0f);
			//material->SetUniformValue<Vector3>("lightColor", Vector3(1.0f));
			//material->SetUniformValue<Vector3>("lightPos", Vector3(1.0f));

			//shader = std::make_shared<Shader>(shaderPath);
			//shader->Bind();
			//shader->SetInt("tex", 0);
			//shader->SetFloat("intensity", 1.0f);
			//shader->SetColor("lightColor", Vector3(1.0f));
			//shader->SetVector3("lightPos", Vector3(0.0f));
		}

		//// TODO: 验证文件是否存在
		//if (texturePath != "")
		//{
		//	texture = std::make_unique<Texture>(texturePath);
		//}
	}

	void MeshRenderer::SetMesh(Mesh* mesh, const std::string& vertShader, const std::string& fragShader)
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
		if (vertShader != "" && fragShader != "")
		{
			material = std::make_shared<Material>(new Shader(vertShader, fragShader));
			material->SetAlbedoMap("Resources/Textures/nuwa.png");
			material->SetSpecularMap("Resources/Textures/black.png");
		}
	}

	void MeshRenderer::OnInspectorGUI()
	{
#ifdef NUWA_EDITOR
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
			//EditorGUI::DrawLabel("Shader", material->GetShaderPath());
			EditorGUI::DrawLabel("Albedo Map", material->albedoMap);
			EditorGUI::DrawEditColor3("Base Color", Global::DiffuseColor);
			EditorGUI::DrawLabel("Specular Map", material->specularMap);
			// more...
			ImGui::Unindent();
		}
#endif // NUWA_EDITOR
	}
}
