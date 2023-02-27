#pragma once
#include "BehaviorComponent.h"

namespace Nuwa
{
	class Camera;
	class CameraView : public BehaviorComponent
	{
	public:
		CameraView(Camera* camera);
		virtual ~CameraView();

		virtual void Start() override;
		virtual void Update() override;

		Camera* target;
		float speed;
		float sensitivity;

	protected:
		virtual void OnInspectorGUI() override;		

	private:
		bool isActive;
	};
}
