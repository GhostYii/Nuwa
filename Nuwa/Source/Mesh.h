#pragma once
#include "EngineTypes.h"
#include "Graphics/MeshVertex.h"
#include <vector>

namespace Nuwa
{
	class Mesh
	{
	public:
		Mesh();
		virtual ~Mesh() = default;

		void SetMeshVertices(std::vector<MeshVertex> vertices, std::vector<uint> indices);

		inline std::vector<MeshVertex> GetVertices() { return vertices; }
		inline std::vector<uint> GetIndices() { return indices; }

		uint GetVerticesSize();
		uint GetIndicesSize();

		uint GetVerticesCount();
		uint GetIndicesCount();

	private:
		std::vector<MeshVertex> vertices;
		std::vector<uint> indices;	
	};
}

