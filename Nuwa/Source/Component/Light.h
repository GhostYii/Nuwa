#pragma once
#include "BehaviorComponent.h"

namespace Nuwa
{
	class Light : public BehaviorComponent
	{
		// 简单模拟冯氏光照模型（phong light model）
	public:		
		Light();
		virtual ~Light() = default;

		// 环境光
		float ambient;
		// 漫反射
		float diffuse;
		// 高光（镜面反射）
		float specular;

		float intensity;

	private:
	};

}