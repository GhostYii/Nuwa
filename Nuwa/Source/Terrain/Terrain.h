#pragma once
#include "../Nuwa.h"
#include "../Component/BehaviorComponent.h"
#include "TerrainVertex.h"

namespace Nuwa
{
	class Terrain : public BehaviorComponent
	{
	public:
		Terrain(const std::string heightMapPath, const std::string mainTexture);
		virtual ~Terrain();

		virtual void InternalRender() override;

	private:
		//std::string heightmapPath;
		//Vector2Int size;

		float heightScale = 64.0f;
		float heightShift = 16.0f;
		int rez = 20;

		VertexArray* vao;
		VertexBuffer* vbo;
		Shader* shader;
		Texture* heightMap;

		Texture* surfaceTex;

		const uint PATCH_COUNT = 4;

	protected:
		virtual void OnInspectorGUI() override;
	};
}