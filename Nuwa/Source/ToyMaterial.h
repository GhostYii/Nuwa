#pragma once
#include "Graphics/Shader.h"

namespace Nuwa
{
	class ToyMaterial
	{
	public:
		ToyMaterial();
		~ToyMaterial();

		bool HasShader() const;

#pragma region SetUniformValue
		template<typename T>
		inline void SetUniformValue(const std::string& name, T value)
		{
			if (!shader)
				return;
			spdlog::warn("Uniform type {} not implement.", typeid(T).name());
		}
		template<>
		inline void SetUniformValue<int>(const std::string& name, int value)
		{
			if (!shader)
				return;
			shader->SetInt(name, value);
		}
		template<>
		inline void SetUniformValue<float>(const std::string& name, float value)
		{
			if (!shader)
				return;
			shader->SetFloat(name, value);

		}
		template<>
		inline void SetUniformValue<Vector3>(const std::string& name, Vector3 value)
		{
			if (!shader)
				return;
			shader->SetVector3(name, value);

		}
		template<>
		inline void SetUniformValue<Vector4>(const std::string& name, Vector4 value)
		{
			if (!shader)
				return;
			shader->SetColor(name, value);

		}
		template<>
		inline void SetUniformValue<Matrix4x4>(const std::string& name, Matrix4x4 value)
		{
			if (!shader)
				return;
			shader->SetMatrix4x4(name, value);
		}
#pragma endregion

	private:
		std::shared_ptr<Shader> shader;
	};
}
