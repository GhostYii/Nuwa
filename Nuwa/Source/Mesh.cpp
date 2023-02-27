#include "Mesh.h"
#include "spdlog/spdlog.h"
#include "obj_loader/tiny_obj_loader.h"

namespace Nuwa
{
	Mesh::Mesh()
		: vertices(std::vector<MeshVertex>()), indices(std::vector<uint>()), modelPath("")
	{
	}

	void Mesh::LoadFromObj(std::string objPath)
	{
		tinyobj::attrib_t attribs;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string err;

		std::string mtlDir = objPath.substr(0, objPath.find_last_of("\\/")) + "/";

		bool isLoaded = tinyobj::LoadObj(&attribs, &shapes, &materials, &err, objPath.c_str(), mtlDir.c_str());

		if (!isLoaded || !err.empty())
		{
			spdlog::error("Load mesh from Obj file failed : {}", err);
			return;
		}

		modelPath = objPath;
		//std::vector<MeshVertex> vertices;
		//std::vector<uint> indices;

		size_t vertexIndexSize = 0;
		for (auto i = 0; i < shapes.size(); ++i)
			vertexIndexSize += shapes[i].mesh.indices.size();

		vertices.reserve(vertexIndexSize);
		indices.reserve(vertexIndexSize);

		size_t indexOffset = 0;
		size_t materialSize = materials.empty() ? 1 : materials.size();
		for (auto m = 0; m < materialSize; ++m)
		{
			for (auto i = 0; i < shapes.size(); ++i)
			{
				size_t offset = 0;
				for (size_t j = 0; j < shapes[i].mesh.num_face_vertices.size(); ++j)
				{
					if (!materials.empty() && shapes[i].mesh.material_ids[j] != m)
						continue;

					uchar faceCount = shapes[i].mesh.num_face_vertices[j];
					for (uchar k = 0; k < faceCount; ++k)
					{
						tinyobj::index_t index = shapes[i].mesh.indices[k + indexOffset];

						Vector3 position = { 0, 0, 0 };
						if (index.vertex_index != -1)
						{
							position.x = attribs.vertices[index.vertex_index * 3 + 0];
							position.y = attribs.vertices[index.vertex_index * 3 + 1];
							position.z = attribs.vertices[index.vertex_index * 3 + 2];
						}

						Vector2 uv = { 0, 0 };
						if (index.texcoord_index != -1)
						{
							uv.x = attribs.texcoords[index.texcoord_index * 2 + 0];
							uv.y = attribs.texcoords[index.texcoord_index * 2 + 1];
						}

						Vector3 normal = { 0, 0, 0 };
						if (index.normal_index != -1)
						{
							normal.x = attribs.normals[index.normal_index * 3 + 0];
							normal.y = attribs.normals[index.normal_index * 3 + 1];
							normal.z = attribs.normals[index.normal_index * 3 + 2];
						}

						vertices.push_back({ position, uv, normal });
						indices.push_back(k + indexOffset);
					}
					offset += faceCount;
					indexOffset += faceCount;
				}
			}
		}
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

	const std::string Mesh::GetModelPath() const
	{
		return modelPath;
	}
}
