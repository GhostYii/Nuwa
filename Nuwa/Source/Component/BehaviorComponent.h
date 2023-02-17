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
		BehaviorComponent() : enable(true) {};
		virtual ~BehaviorComponent() = default;

		bool enable;

		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void Destory() {}

	protected:
		virtual void InternalStart() { Start(); }
		virtual void InternalUpdate() { if (enable) Update(); }
		virtual void InternalLateUpdate() { if (enable) LateUpdate(); }
		virtual void InternalRender() {}

		virtual void InternalOnInspectorGUI();

		virtual void OnInspectorGUI() {}
	};
}