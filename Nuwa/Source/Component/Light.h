#pragma once
#include "BehaviorComponent.h"

namespace Nuwa
{
	//class Shader;
	class GameScene;

	class Light : public BehaviorComponent
	{
		// ��ģ����Ϲ���ģ�ͣ�phong light model��
	public:
		Light();
		virtual ~Light() = default;

		LightType type;

		// ������
		float ambient;
		// ������
		float diffuse;
		// �߹⣨���淴�䣩
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