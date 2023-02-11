#include "Mesh.h"

namespace Nuwa
{
	Mesh::Mesh()
		: vertices(std::vector<MeshVertex>()), indices(std::vector<uint>())
	{
	}

	void Mesh::SetMeshVertices(std::vector<MeshVertex> vertices, std::vector<uint> indices)
	{
		this->vertices = vertices;
		this->indices = indices;
	}

	uint Mesh::GetVerticesSize()
	{
		return vertices.size() * sizeof(MeshVertex);
	}
	uint Mesh::GetIndicesSize()
	{
		return indices.size() * sizeof(uint);
	}
}