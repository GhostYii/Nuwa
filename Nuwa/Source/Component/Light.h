#pragma once
#include "BehaviorComponent.h"

namespace Nuwa
{
	//class Shader;
	class GameScene;

	class Light : public BehaviorComponent
	{
		// 简单模拟冯氏光照模型（phong light model）
	public:
		Light();
		virtual ~Light() = default;

		LightType type;

		// 环境光
		float ambient;
		// 漫反射
		float diffuse;
		// 高光（镜面反射）
		float specular;

		float intensity;

		Vector3 color;

		//virtual void Awake() override;
		virtual void Start() override;
		void SetGameScene(GameScene* gameScene);

	private:
		//std::unique_ptr<Shader> shader;

	protected:
		std::unique_ptr<GameScene> scene;

		virtual void InternalRender() override;
		virtual void OnInspectorGUI() override;
		
		virtual void OnDisable() override;
	};

}