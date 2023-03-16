#include "Terrain.h"
#include "../Component/Camera.h"
#include "stb/stb_image.h"

namespace Nuwa
{
	Terrain::Terrain(const std::string heightMapPath, const std::string mainTexture)
		: vao(nullptr), shader(nullptr), surfaceTex(nullptr), heightMap(nullptr), vbo(nullptr)
	{
		if (heightMapPath.empty())
		{
			spdlog::error("terrain must have height map.");
			return;
		}

		heightMap = new Texture(heightMapPath);

		if (!mainTexture.empty())
			surfaceTex = new Texture(mainTexture);

		float width = heightMap->Width(), height = heightMap->Height();
		std::vector<TerrainVertex> vertices;

		for (uint i = 0; i < rez; ++i)
		{
			for (uint j = 0; j < rez; ++j)
			{
				vertices.push_back
				({
					{-width / 2.0f + width * i / (float)rez, 0, -height / 2.0f + height * j / (float)rez},
					{i / float(rez), j / float(rez)}
				});

				vertices.push_back
				({
					{-width / 2.0f + width * (i + 1) / (float)rez, 0, -height / 2.0f + height * j / (float)rez},
					{(i + 1) / (float)rez, j / float(rez)}
				});

				vertices.push_back
				({
					{-width / 2.0f + width * i / (float)rez, 0, -height / 2.0f + height * (j + 1) / (float)rez},
					{i / float(rez), (j + 1) / (float)rez}
				});

				vertices.push_back
				({
					{-width / 2.0f + width * (i + 1) / (float)rez, 0, -height / 2.0f + height * (j + 1) / (float)rez},
					{(i + 1) / float(rez), (j + 1) / float(rez)}
				});
			}
		}

		GL_ASSERT(glPatchParameteri(GL_PATCH_VERTICES, PATCH_COUNT));

		vao = new VertexArray();
		vbo = new VertexBuffer(vertices.data(), vertices.size() * sizeof(TerrainVertex));
		VertexLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		vao->AddBuffer(*vbo, layout);

		std::unordered_map<ShaderType, std::string> paths =
		{
			{ ShaderType::Vertex, "Resources/Shaders/Terrain.vert" },
			{ ShaderType::TessControl, "Resources/Shaders/Terrain.tesc" },
			{ ShaderType::TessEvaluation, "Resources/Shaders/Terrain.tese" },
			{ ShaderType::Fragment, "Resources/Shaders/Terrain.frag" }
		};

		shader = new Shader(paths);
	}

	Terrain::~Terrain()
	{
		delete heightMap;
		delete surfaceTex;
		delete vao;
		delete vbo;
		delete shader;
	}

	void Terrain::InternalRender()
	{
		if (!GameScene::mainCamera)
			return;

		if (!gameObject->IsActive())
			return;

		if (!vao || !shader)
			return;

		heightMap->Bind();
		if (surfaceTex)
			surfaceTex->Bind(1);

		vao->Bind();
		shader->Bind();

		shader->SetInt("heightMap", 0);
		shader->SetInt("mainTex", 1);
		shader->SetFloat("yScale", heightScale);
		shader->SetFloat("yShift", heightShift);
		shader->SetMatrix4x4("model", transform->GetModelMatrix());

		GL_ASSERT(glDrawArrays(GL_PATCHES, 0, PATCH_COUNT * rez * rez));
	}

	void Terrain::OnInspectorGUI()
	{
#ifdef NUWA_EDITOR
		EditorGUI::DrawLabel("Height Map", heightMap->Filepath());
		EditorGUI::DrawSlideFloat("Height Scale", heightScale, 0, 256);
		EditorGUI::DrawDragFloat("Height Shift", heightShift);
#endif // NUWA_EDITOR
	}
}