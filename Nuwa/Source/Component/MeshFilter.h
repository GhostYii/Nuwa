#pragma once
#include "Component.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Nuwa
{
	class Mesh;
	//class MeshRenderer;
	class MeshFilter : public Component
	{
		friend class MeshRenderer;
	public:
		MeshFilter();
		virtual ~MeshFilter();

		//Mesh* mesh;

		void LoadMeshFromFile(std::string path);
		Mesh* GetMesh();

	protected:
		virtual void OnInspectorGUI() override;

	private:
		std::string filepath;
		std::string dir;
		// 由于目前不支持父子关系，所以暂时将模型所有网格都合并到一个结构里
		std::vector<Mesh> cachedMeshes;
		//MeshRenderer* meshRenderer;

		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}