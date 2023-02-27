#include "CameraView.h"
#include "Camera.h"
#include "../GameObject.h"
#include "../Input/Input.h"
#include "../Time.h"

namespace Nuwa
{
	CameraView::CameraView(Camera* camera)
		: speed(5.0f), sensitivity(0.1f), target(camera), isActive(true)
	{
	}

	CameraView::~CameraView()
	{
	}

	void CameraView::Start()
	{
		if (!target)
			return;
	}

	void CameraView::Update()
	{
		if (!target)
			return;

		if (Input::GetKeyDown(KeyCode::LeftAlt))
			isActive = !isActive;

		Input::SetCursorMode(isActive ? CursorMode::Disabled : CursorMode::Normal);
		if (!isActive)
			return;

		// view control
		Vector2 viewOffset = Input::GetMouseMove() * sensitivity;
		Vector3 newEuler = target->transform->eulerAngles - Vector3(viewOffset.y, viewOffset.x, 0);
		newEuler.x = newEuler.x > 89.0f ? 89.0f : (newEuler.x < -89.0f ? -89.0f : newEuler.x);
		target->transform->eulerAngles = newEuler;

		// move control
		float right = 0, forward = 0;
		if (Input::GetKey(KeyCode::W))
			forward = 1;
		else if (Input::GetKey(KeyCode::S))
			forward = -1;

		if (Input::GetKey(KeyCode::A))
			right = -1;
		else if (Input::GetKey(KeyCode::D))
			right = 1;

		Vector3 posOffset = target->transform->Right() * right + target->transform->Forward() * forward;
		posOffset *= speed * Time::deltaTime;
		target->transform->position += posOffset;
	}

	void CameraView::OnInspectorGUI()
	{
#ifdef NUWA_EDITOR
		EditorGUI::DrawToggle("Input Enable", isActive);
		EditorGUI::DrawLabel("Camera Target", target->gameObject->name);
		EditorGUI::DrawDragFloat("Speed", speed);
		EditorGUI::DrawSlideFloat("Sensitivity", sensitivity, 0.05, 1);
#endif // NUWA_EDITOR
	}


}