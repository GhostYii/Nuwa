#pragma once
#include "InputSystem.h"
#include <unordered_map>

namespace Nuwa
{	
	class Input
	{
		friend class InputSystem;
	private:
		Input() = default;
		~Input() = default;

		// Value: previous state, current state
		static std::unordered_map<KeyCode, KeyStatePair> keyStates;
		static std::unordered_map<MouseButton, KeyStatePair> mouseButtonStates;
		static Vector2 mousePosition;
		static bool isMouseWheelInput;
		static float mouseWheel;
		static Vector2 mouseDelta;

	public:
		//static bool AnyKey();
		static bool GetKeyDown(KeyCode key);
		static bool GetKey(KeyCode key);
		static bool GetKeyUp(KeyCode key);
		static KeyState GetKeyState(KeyCode key);

		//static bool AnyMouseInput();
		static bool GetMouseKeyDown(MouseButton button);
		static bool GetMouseKey(MouseButton button);
		static bool GetMouseKeyUp(MouseButton button);
		static KeyState GetMouseButtonState(MouseButton button);

		static Vector2 GetMouseMove();
		static float GetMouseWheel();
		static Vector2 GetMousePosition();
		static bool IsMouseMove();

		static void SetCursorVisble(bool visible);

		inline static KeyStatePair get_pair(KeyCode key) { return keyStates[key]; }
	};
}