#pragma once
#include "../EngineTypes.h"
#include <GLFW/glfw3.h>

#include "../Graphics/ToyRenderer.h"

namespace Nuwa
{
	struct WindowConfig
	{
		int width;
		int height;
		std::string title;
		Vector4 backgroundColor;
	};

	class NwWindow
	{
	public:
		NwWindow();
		virtual ~NwWindow();

		bool IsRun();

		void InitImGui();
		void Start();
		void Update();
		void Close();

		inline int Width() const { return config.width; }
		inline int Height() const { return config.height; }
		inline std::string Title() const { return config.title; }
		inline const GLFWwindow* GlfwWindow() const { return window; }

	protected:
		GLFWwindow* window;
		WindowConfig config;
		ToyRenderer* renderer = nullptr;

		virtual void OnStart() {}
		virtual void OnGUI() {}
		virtual void OnUpdate() {}
		virtual void OnRenderObject() {}
	};
}


