#include "InputSystem.h"
#include "Input.h"
#include "../GameWindow.h"

namespace Nuwa
{
	InputSystem* InputSystem::instance = nullptr;	

	InputSystem::InputSystem()
		: currentCursorMode(CursorMode::Normal), isInited(false)
	{

	}

	InputSystem* InputSystem::GetInstance()
	{
		return instance;
	}

	void InputSystem::CreateInstance()
	{
		if (InputSystem::instance)
			return;
		//delete instance;
		instance = new InputSystem();
	}

	void InputSystem::ReleaseInstance()
	{
		if (!InputSystem::instance)
			return;

		delete InputSystem::instance;
	}

	void InputSystem::Init(const NwWindow& window)
	{
		if (isInited)
			return;

		auto glfwWnd = const_cast<GLFWwindow*>(window.GlfwWindow());
		// keyboard
		glfwSetKeyCallback(glfwWnd, OnGLFWKeyCallback);
		//glfwSetInputMode(glfwWnd, GLFW_STICKY_KEYS, GLFW_TRUE);

		// mouse
		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(glfwWnd, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		glfwSetCursorPosCallback(glfwWnd, OnGLFWCursorPositionCallback);
		glfwSetMouseButtonCallback(glfwWnd, OnGLFWMouseButtonCallback);
		glfwSetScrollCallback(glfwWnd, OnGLFWMouseScrollCallback);
		double x, y;
		glfwGetCursorPos(glfwWnd, &x, &y);
		prevMousePos = { x, y };
		// TODO: joystick

		isInited = true;
		spdlog::info("Input System inited.");
	}

	void InputSystem::Update(const NwWindow& window)
	{
		if (!isInited)
			return;

		auto glfwWnd = const_cast<GLFWwindow*>(window.GlfwWindow());
		glfwSetInputMode(glfwWnd, GLFW_CURSOR, (uint)currentCursorMode);

		double x, y;
		glfwGetCursorPos(glfwWnd, &x, &y);
		Input::mouseDelta = { x - prevMousePos.x, y - prevMousePos.y };
		prevMousePos = { x, y };

		for (auto pair : Input::keyStates)
		{
			auto prev = Input::GetKeyState(pair.first);

			Input::keyStates[pair.first].first = prev;
			Input::keyStates[pair.first].second = (KeyState)glfwGetKey(glfwWnd, (int)pair.first);
		}
		for (auto pair : Input::mouseButtonStates)
		{
			auto prev = Input::GetMouseButtonState(pair.first);

			Input::mouseButtonStates[pair.first].first = prev;
			Input::mouseButtonStates[pair.first].second = (KeyState)glfwGetMouseButton(glfwWnd, (int)pair.first);
		}
	}

	void InputSystem::SetCursorVisible(bool visible)
	{
		if (!isInited)
		{
			spdlog::warn("Input System not inited.");
			return;
		}

		currentCursorMode = visible ? CursorMode::Normal : CursorMode::Hidden;
	}

	void InputSystem::SetCursorMode(CursorMode mode)
	{
		currentCursorMode = mode;
	}

	void InputSystem::OnGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (Input::keyStates.find((KeyCode)key) == Input::keyStates.end())
			Input::keyStates.insert_or_assign((KeyCode)key, KeyStatePair(KeyState::Released, KeyState::Released));
	}

	void InputSystem::OnGLFWCursorPositionCallback(GLFWwindow* window, double x, double y)
	{
		Input::mousePosition = Vector2(x, y);
	}

	void InputSystem::OnGLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (Input::mouseButtonStates.find((MouseButton)button) == Input::mouseButtonStates.end())
			Input::mouseButtonStates.insert_or_assign((MouseButton)button, KeyStatePair(KeyState::Released, KeyState::Released));
	}

	void InputSystem::OnGLFWMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		Input::isMouseWheelInput = true;
		Input::mouseWheel = yOffset;
	}
}