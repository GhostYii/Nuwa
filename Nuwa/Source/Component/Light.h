#pragma once
#include "BehaviorComponent.h"

namespace Nuwa
{
	class Light : public BehaviorComponent
	{
		// ��ģ����Ϲ���ģ�ͣ�phong light model��
	public:		
		Light();
		virtual ~Light() = default;

		// ������
		float ambient;
		// ������
		float diffuse;
		// �߹⣨���淴�䣩
		float specular;

		float intensity;

	private:
	};

}