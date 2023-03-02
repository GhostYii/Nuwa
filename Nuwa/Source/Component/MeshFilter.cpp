#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "../Mesh.h"
#include "../GameObject.h"

namespace Nuwa
{
	MeshFilter::MeshFilter()
		: dir(""), cachedMeshes(std::vector<Mesh>()), filepath("")
	{
	}

	MeshFilter::~MeshFilter()
	{
	}

	void MeshFilter::LoadMeshFromFile(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			spdlog::error("Load mesh from file failed : {}", importer.GetErrorString());
			return;
		}

		filepath = path;
		dir = filepath.substr(0, filepath.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);

		if (gameObject)
		{
			auto meshRenderers = gameObject->GetComponents<MeshRenderer>();
			for (auto mr : meshRenderers)
			{
				//mr->mesh = std::make_shared<Mesh>(*GetMesh());
				mr->ResetMeshDrawData(this);
			}
		}
	}

	Mesh* MeshFilter::GetMesh()
	{
		//if (cachedMeshes.empty())
		//	return nullptr;

		Mesh* mesh = new Mesh();
		std::vector<MeshVertex> vertices;
		std::vector<uint> indices;

		uint beg = 0;
		for (auto& cachedMesh : cachedMeshes)
		{
			auto v = cachedMesh.GetVertices();
			auto i = cachedMesh.GetIndices();
			for (auto& idx : cachedMesh.GetIndices())
				idx += beg;

			vertices.insert(vertices.end(), v.begin(), v.end());
			indices.insert(indices.end(), i.begin(), i.end());

			beg += v.size();
		}

		mesh->SetMeshVertices(vertices, indices);
		return mesh;
	}

	void MeshFilter::OnInspectorGUI()
	{
#ifdef NUWA_EDITOR
		if (cachedMeshes.empty())		
			EditorGUI::DrawSingleText("Not load mesh.");
		else
			EditorGUI::DrawLabel("Mesh Path", filepath);
				
		int vc = 0;
		for (auto mesh : cachedMeshes)
			vc += mesh.GetVerticesCount();

		ImGui::BeginDisabled();
		EditorGUI::DrawDragInt("Verts", vc);
		ImGui::EndDisabled();
#endif // NUWA_EDITOR
	}

	void MeshFilter::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (uint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			Mesh m = ProcessMesh(mesh, scene);
			cachedMeshes.push_back(m);
		}

		for (uint i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh MeshFilter::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		Mesh cachedMesh;

		std::vector<MeshVertex> vertices;
		std::vector<uint> indices;
		//std::vector<Texture> textures;

		for (uint i = 0; i < mesh->mNumVertices; i++)
		{
			Vector3 position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
			Vector2 texcoord(0);
			if (mesh->mTextureCoords[0])
			{
				texcoord.x = mesh->mTextureCoords[0][i].x;
				texcoord.y = mesh->mTextureCoords[0][i].y;
			}
			Vector3 normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

			vertices.push_back({ position, texcoord, normal });
		}

		for (uint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (uint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		cachedMesh.SetMeshVertices(vertices, indices);
		return cachedMesh;
	}
}