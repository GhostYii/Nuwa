#pragma once
#include "Renderer.h"

namespace Nuwa
{
	class SpriteRenderer : public Renderer
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer() = default;

		void SetSprite(std::string path);

	protected:
		//virtual void Draw() override;
		virtual void OnInspectorGUI() override;
	private:
		std::string spritePath;
	};
}