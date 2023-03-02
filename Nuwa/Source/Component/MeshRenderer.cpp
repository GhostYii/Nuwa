#include "MeshRenderer.h"
#include "../GameObject.h"
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
		GL_ASSERT(glEnable(GL_BLEND));
		GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	}

	//void MeshRenderer::SetMesh(Mesh* mesh, const std::string& shaderPath)
	//{
	//	this->mesh = std::make_shared<Mesh>(*mesh);

	//	GL_ASSERT(glEnable(GL_BLEND));
	//	GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//	vao = std::make_unique<VertexArray>();
	//	vbo = std::make_unique<VertexBuffer>(mesh->GetVertices().data(), mesh->GetVerticesSize());

	//	VertexLayout layout;
	//	layout.Push<float>(3);	//pos
	//	layout.Push<float>(2);	//uv
	//	layout.Push<float>(3);	//norm

	//	vao->AddBuffer(*vbo, layout);

	//	ibo = std::make_unique<IndexBuffer>(mesh->GetIndices().data(), mesh->GetIndicesSize());

	//	// TODO: 验证文件是否存在
	//	if (shaderPath != "")
	//	{
	//		material = std::make_shared<Material>(new Shader(shaderPath));
	//		material->SetAlbedoMap("Resources/Textures/albedo.jpg");
	//		material->SetSpecularMap("Resources/Textures/albedo.jpg");
	//	}
	//}

	//void MeshRenderer::SetMesh(Mesh* mesh, const std::string& vertShader, const std::string& fragShader)
	//{
	//	this->mesh = std::make_shared<Mesh>(*mesh);

	//	GL_ASSERT(glEnable(GL_BLEND));
	//	GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//	vao = std::make_unique<VertexArray>();
	//	vbo = std::make_unique<VertexBuffer>(mesh->GetVertices().data(), mesh->GetVerticesSize());

	//	VertexLayout layout;
	//	layout.Push<float>(3);	//pos
	//	layout.Push<float>(2);	//uv
	//	layout.Push<float>(3);	//norm

	//	vao->AddBuffer(*vbo, layout);

	//	ibo = std::make_unique<IndexBuffer>(mesh->GetIndices().data(), mesh->GetIndicesSize());

	//	// TODO: 验证文件是否存在
	//	if (vertShader != "" && fragShader != "")
	//	{
	//		material = std::make_shared<Material>(new Shader(vertShader, fragShader));
	//		material->SetAlbedoMap("Resources/Textures/albedo.jpg");
	//		material->SetSpecularMap("Resources/Textures/albedo.jpg");
	//	}
	//}

	void MeshRenderer::SetMaterial(Material* material)
	{
		this->material = std::make_shared<Material>(*material);
	}

	void MeshRenderer::Start()
	{
		auto filter = std::make_shared<MeshFilter>(*(gameObject->GetComponent<MeshFilter>()));
		if (!filter)
			return;
		
		mesh = std::make_shared<Mesh>(*(filter->GetMesh()));
		if (!mesh->GetIndicesSize())
		{
			spdlog::error("fuck");
			return;
		}
		vao = std::make_unique<VertexArray>();
		vbo = std::make_unique<VertexBuffer>(mesh->GetVertices().data(), mesh->GetVerticesSize());

		VertexLayout layout;
		layout.Push<float>(3);	//pos
		layout.Push<float>(2);	//uv
		layout.Push<float>(3);	//norm

		vao->AddBuffer(*vbo, layout);

		ibo = std::make_unique<IndexBuffer>(mesh->GetIndices().data(), mesh->GetIndicesSize());
	}

	void MeshRenderer::OnInspectorGUI()
	{
#ifdef NUWA_EDITOR
		if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Indent();
			std::string filepaths;
			for (auto path : material->GetShaderPaths())
			{
				filepaths += path;
				if (path != material->GetShaderPaths().back())
					filepaths += ",";
			}

			EditorGUI::DrawLabel("Shader", filepaths);
			EditorGUI::DrawLabel("Albedo Map", material->albedoMap);
			EditorGUI::DrawLabel("Specular Map", material->specularMap);
			// more...
			ImGui::Unindent();
		}
#endif // NUWA_EDITOR
	}

	void MeshRenderer::ResetMeshDrawData(MeshFilter* filter)
	{
		//auto filter = std::make_shared<MeshFilter>(*(gameObject->GetComponent<MeshFilter>()));
		if (!filter)
			return;

		mesh = std::make_shared<Mesh>(*filter->GetMesh());

		vbo->Reset(mesh->GetVertices().data(), mesh->GetVerticesSize());

		VertexLayout layout;
		layout.Push<float>(3);	// pos
		layout.Push<float>(2);	// uv
		layout.Push<float>(3);	// norm

		vao->Reset();
		vao->AddBuffer(*vbo, layout);

		ibo->Reset(mesh->GetIndices().data(), mesh->GetIndicesSize());
	}
}
