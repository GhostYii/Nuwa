#pragma once
#include "../EngineMacros.h"
#include "../EngineTypes.h"
#include "../Transform.h"

#ifdef NUWA_EDITOR
#include "../Editor/Editor.h"
using namespace Nuwa::Editor;
#endif // NUWA_EDITOR

namespace Nuwa
{
	class GameObject;
	
	class Component
	{
#ifdef NUWA_EDITOR
		friend class Inspector;
#endif // NUWA_EDITOR
	public:
		Component();
		virtual ~Component() = default;

		GameObject* gameObject;
		Transform* transform;

		void AttachToGameObject(GameObject* gameObject);

		const uint64 GetInstanceID() const;

	protected:
		uint64 instanceID;

		virtual void InternalOnInspectorGUI();
		virtual void OnInspectorGUI() {}
	};
}

