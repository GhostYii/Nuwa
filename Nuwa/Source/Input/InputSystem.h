#pragma once
#include "../EngineTypes.h"

namespace Nuwa
{
	class NwWindow;
	class InputSystem
	{
	private:
		InputSystem();
		~InputSystem() = default;

	public:
		static InputSystem* GetInstance();
		static void CreateInstance();
		static void ReleaseInstance();

		void Init(const NwWindow& window);
		void Update(const NwWindow& window);

		void SetCursorVisible(bool visible);

	private:
		static InputSystem* instance;

		bool isInited;
		Vector2 prevMousePos = {};
		CursorMode currentCursorMode;

		static void OnGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void OnGLFWCursorPositionCallback(GLFWwindow* window, double x, double y);
		static void OnGLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void OnGLFWMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	};
}