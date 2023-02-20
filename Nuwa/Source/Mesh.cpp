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

		std::string mtlDir = objPath.substr(0, objPath.find_last_of("\\/"));

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

		//vertices.reserve(vertexIndexSize);
		//indices.reserve(vertexIndexSize);

		size_t indexOffset = 0;
		//for (auto m = 0; m < materials.size(); ++m)
		{
			for (auto i = 0; i < shapes.size(); ++i)
			{
				size_t offset = 0;
				for (size_t j = 0; j < shapes[i].mesh.num_face_vertices.size(); ++j)
				{
					//if (shapes[i].mesh.material_ids[j] != m)
					//	continue;

					uchar faceCount = shapes[i].mesh.num_face_vertices[j];
					for (uchar k = 0; k < faceCount; ++k)
					{
						tinyobj::index_t index = shapes[i].mesh.indices[k + indexOffset];

						tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
						tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
						tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

						tinyobj::real_t u = attribs.texcoords[index.texcoord_index * 2 + 0];
						tinyobj::real_t v = attribs.texcoords[index.texcoord_index * 2 + 1];

						tinyobj::real_t nx = attribs.normals[index.normal_index * 3 + 0];
						tinyobj::real_t ny = attribs.normals[index.normal_index * 3 + 1];
						tinyobj::real_t nz = attribs.normals[index.normal_index * 3 + 2];

						vertices.push_back({ Vector3(vx, vy, vz), Vector2(u, v), Vector3(nx,ny,nz) });
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
