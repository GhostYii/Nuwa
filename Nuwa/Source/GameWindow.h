#pragma once
#include "Core/NwWindow.h"
#include <memory>

// for test
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Graphics/VertexLayout.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexArray.h"
#include "Graphics/IndexBuffer.h"

namespace Nuwa
{
	class GameWindow : public NwWindow
	{
	public:
		GameWindow(const WindowConfig& config);
		virtual ~GameWindow() {}

	protected:
		virtual void OnStart() override;
		virtual void OnGUI() override;
		virtual void OnUpdate() override;
		virtual void OnRenderObject() override;

		static void OnFrameBufferSizeChanged(GLFWwindow* window, int width, int height);

	private:
		// for test
		VertexArray* vao;
		VertexBuffer* vbo;
		IndexBuffer* ibo;
		Shader* shader;
		Texture* texture;
	};

}