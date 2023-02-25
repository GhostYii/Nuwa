#include "Input.h"

namespace Nuwa
{
	std::unordered_map<KeyCode, std::pair<KeyState, KeyState>> Input::keyStates;
	std::unordered_map<MouseButton, std::pair<KeyState, KeyState>> Input::mouseButtonStates;
	Vector2 Input::mouseDelta;
	Vector2 Input::mousePosition;
	bool Input::isMouseWheelInput = false;
	float Input::mouseWheel;

	bool Input::GetKeyDown(KeyCode key)
	{
		if (keyStates.find(key) == keyStates.end())
			keyStates.insert_or_assign(key, KeyStatePair(KeyState::Released, KeyState::Released));

		return keyStates[key].first == KeyState::Released && keyStates[key].second != KeyState::Released;
	}

	bool Input::GetKey(KeyCode key)
	{
		if (keyStates.find(key) == keyStates.end())
			keyStates.insert_or_assign(key, KeyStatePair(KeyState::Released, KeyState::Released));

		return keyStates[key].second != KeyState::Released;
	}

	bool Input::GetKeyUp(KeyCode key)
	{
		if (keyStates.find(key) == keyStates.end())
			keyStates.insert_or_assign(key, KeyStatePair(KeyState::Released, KeyState::Released));

		return keyStates[key].first != KeyState::Released && keyStates[key].second == KeyState::Released;
	}

	KeyState Input::GetKeyState(KeyCode key)
	{
		if (keyStates.find(key) == keyStates.end())
			keyStates.insert_or_assign(key, KeyStatePair(KeyState::Released, KeyState::Released));

		return keyStates[key].second;
	}

	bool Input::GetMouseKeyDown(MouseButton button)
	{
		if (mouseButtonStates.find(button) == mouseButtonStates.end())
			mouseButtonStates.insert_or_assign(button, KeyStatePair(KeyState::Released, KeyState::Released));

		return mouseButtonStates[button].first == KeyState::Released && mouseButtonStates[button].second != KeyState::Released;
	}

	bool Input::GetMouseKey(MouseButton button)
	{
		if (mouseButtonStates.find(button) == mouseButtonStates.end())
			mouseButtonStates.insert_or_assign(button, KeyStatePair(KeyState::Released, KeyState::Released));

		return mouseButtonStates[button].second != KeyState::Released;
	}

	bool Input::GetMouseKeyUp(MouseButton button)
	{
		if (mouseButtonStates.find(button) == mouseButtonStates.end())
			mouseButtonStates.insert_or_assign(button, KeyStatePair(KeyState::Released, KeyState::Released));

		return mouseButtonStates[button].first != KeyState::Released && mouseButtonStates[button].second == KeyState::Released;
	}

	KeyState Input::GetMouseButtonState(MouseButton button)
	{
		if (mouseButtonStates.find(button) == mouseButtonStates.end())
			mouseButtonStates.insert_or_assign(button, KeyStatePair(KeyState::Released, KeyState::Released));

		return mouseButtonStates[button].second;
	}

	Vector2 Input::GetMouseMove()
	{
		return mouseDelta;
	}

	float Input::GetMouseWheel()
	{
		return mouseWheel;
	}

	Vector2 Input::GetMousePosition()
	{
		return mousePosition;
	}

	bool Input::IsMouseMove()
	{
		return GetMouseMove().length();
	}

	void Input::SetCursorVisble(bool visible)
	{
		InputSystem::GetInstance()->SetCursorVisible(visible);
	}
}