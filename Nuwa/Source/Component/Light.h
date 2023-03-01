#pragma once
#include "BehaviorComponent.h"

namespace Nuwa
{
	class GameScene;

	class Light : public BehaviorComponent
	{
		// 简单模拟冯氏光照模型（phong light model）
	public:
		Light();
		virtual ~Light() = default;

		LightType type;
		float intensity;
		Vector3 color;

		virtual void Start() override;

		// TODO: multi-lights
		virtual void OnEnable() override;
		virtual void OnDisable() override;

		void SetGameScene(GameScene* gameScene);

	protected:
		std::unique_ptr<GameScene> scene;

		virtual void OnInspectorGUI() override;
	};

}