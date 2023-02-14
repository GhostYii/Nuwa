#pragma once
#include "Component.h"

namespace Nuwa
{
	class BehaviorComponent : public Component
	{
	public:
		BehaviorComponent() = default;
		virtual ~BehaviorComponent() = default;

		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void Destory() {}

	protected:
		virtual void InternalStart() { Start(); }
		virtual void InternalUpdate() { Update(); }
		virtual void InternalLateUpdate() { LateUpdate(); }
		virtual void InternalRender() {}
	};
}