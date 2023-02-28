#pragma once
#include "Shader.h"
#include <unordered_set>
#include "../EngineTypes.h"
#include "../EngineMacros.h"
#include "spdlog/spdlog.h"

namespace Nuwa
{
	class Texture;
	class Light;

	class Material
	{
		friend class Renderer;
		friend class Light;
	public:
		Material();
		Material(Shader* shader);
		virtual ~Material();

	public:
		Vector4 baseColor;
		std::string albedoMap;

		// [0, 1]
		float matallic;
		// [0, 1]
		float smoothness;
		std::string metallicMap;

		std::string specularMap;

		std::string normalMap;

		std::string emissionMap;

		//Vector2 tiling;
		//Vector2 offset;

		void SetShader(Shader* shader);
		void SetAlbedoMap(std::string path);
		void SetSpecularMap(std::string path);
		//void SetNormalMap(std::string path);
		//void SetEmissionMap(std::string path);

		std::string GetShaderPath() const;
		
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
		Shader* shader;
		//std::vector<Texture*> textures;
		Texture* textures[MAX_TEXTURE_COUNT];
		std::unordered_map<LightType, std::unordered_set<Light*>> lights;

		void AddLight(Light* light);
		void RemoveLight(Light* light);

		void Apply();
	};
}