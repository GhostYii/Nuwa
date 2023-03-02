#pragma once
#include "Component.h"

#ifdef NUWA_EDITOR
#include "../Editor/Editor.h"
using namespace Nuwa::Editor;
#endif // NUWA_EDITOR

namespace Nuwa
{
	class BehaviorComponent : public Component
	{
		friend class GameScene;
#ifdef NUWA_EDITOR
		friend class Inspector;
#endif // NUWA_EDITOR
	public:
		BehaviorComponent() : enable(true), prevEnable(false) {};
		virtual ~BehaviorComponent() = default;

		bool enable;

		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void Destory() {}

		virtual void OnEnable() {}
		virtual void OnDisable() {}

	protected:
		virtual void InternalStart() { Start(); }
		virtual void InternalUpdate();
		virtual void InternalLateUpdate();
		virtual void InternalRender() {}

		virtual void InternalOnInspectorGUI() override;

		virtual void OnInspectorGUI() override {}

	private:
		bool prevEnable;
	};
}