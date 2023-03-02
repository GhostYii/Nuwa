#include "Mesh.h"
#include <spdlog/spdlog.h>
#include "obj_loader/tiny_obj_loader.h"

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

	uint Mesh::GetVerticesCount()
	{
		return vertices.size();
	}

	uint Mesh::GetIndicesCount()
	{
		return indices.size();
	}
}
