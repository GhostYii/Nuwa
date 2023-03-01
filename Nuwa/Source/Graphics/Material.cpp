#include "Material.h"
#include "Texture.h"
#include "spdlog/spdlog.h"
#include "../Component/Light.h"
#include "../Global.h"

namespace Nuwa
{
	Material::Material()
		: shader(nullptr),
		/*baseColor(Vector4(1)),*/ albedoMap(""),
		//matallic(0.5f), smoothness(0.5f), metallicMap(""),
		specularMap("")
		//normalMap(""),
		//emissionMap("")
	{
		for (int i = 0; i < MAX_TEXTURE_COUNT; i++)
			textures[i] = nullptr;
	}

	Material::Material(Shader* shader)
		:shader(shader),
		/*baseColor(Vector4(1)),*/ albedoMap(""),
		//matallic(0.5f), smoothness(0.5f), metallicMap(""),
		specularMap("")
		//normalMap(""),
		//emissionMap("")
	{
		for (int i = 0; i < MAX_TEXTURE_COUNT; i++)
			textures[i] = nullptr;

		SetShader(shader);
	}

	Material::~Material()
	{
	}

	void Material::SetShader(Shader* shader)
	{
		this->shader = shader;

		if (!shader)
			return;

		shader->SetInt("material.diffuseMap", ALBEDO_MAP_INDEX);
		shader->SetInt("material.specularMap", SPECULAR_MAP_INDEX);
		shader->SetColor("material.plm.ambient", Global::AmbientColor);
		shader->SetFloat("material.plm.ambientAmount", 0.2f);
		shader->SetColor("material.plm.diffuse", Global::DiffuseColor);
		shader->SetFloat("material.plm.diffuseAmount", 1.0f);
		shader->SetColor("material.plm.specular", Global::SpecularColor);
		//shader->SetInt("material.normalMap", NORMAL_MAP_INDEX);
		//shader->SetInt("material.emissionMap", EMISSION_MAP_INDEX);
		shader->SetFloat("material.shininess", 128);
	}

	void Material::SetAlbedoMap(std::string path)
	{
		if (!shader)
			return;
		
		textures[ALBEDO_MAP_INDEX] = new Texture(path);
		shader->SetInt("material.diffuseMap", ALBEDO_MAP_INDEX);
		albedoMap = path;
	}

	void Material::SetSpecularMap(std::string path)
	{
		if (!shader)
			return;
		
		textures[SPECULAR_MAP_INDEX] = new Texture(path);
		shader->SetInt("material.specularMap", SPECULAR_MAP_INDEX);
		specularMap = path;
	}

	std::vector<std::string> Material::GetShaderPaths() const
	{
		if (shader)
			return shader->Filepaths();
		else
			return {};
	}

	void Material::Apply()
	{
		if (!shader)
			return;

		shader->SetColor("material.plm.ambient", Global::AmbientColor);
		//shader->SetFloat("material.plm.ambientAmount", 0.2f);
		shader->SetColor("material.plm.diffuse", Global::DiffuseColor);
		//shader->SetFloat("material.plm.diffuseAmount", 1.0f);
		shader->SetColor("material.plm.specular", Global::SpecularColor);

		shader->SetFloat("material.diffuseAmount", 1.0f);
		//shader->SetFloat("material.shininess", 128);

		for (int i = 0; i < MAX_TEXTURE_COUNT; i++)
		{
			if (textures[i])
				textures[i]->Bind(i);
		}

		// TODO: support realtime change light type
		for (auto iter : lights)
		{
			auto type = iter.first;
			auto attached = iter.second;
			int pidx = 0, didx = 0;
			for (auto light : attached)
			{			
				if (type == LightType::Point)
				{
					std::string perfix = "pLights[" + std::to_string(pidx++) + "].";
					shader->SetVector3(perfix + "position", light->transform->position);
					shader->SetVector3(perfix + "color", light->color);
					shader->SetFloat(perfix + "intensity", light->intensity);
					shader->SetFloat(perfix + "kc", 1.0f);
					shader->SetFloat(perfix + "kl", 0.09f);
					shader->SetFloat(perfix + "kq", 0.032f);
				}
				else if (type == LightType::Direction)
				{
					std::string perfix = "dLights[" + std::to_string(didx++) + "].";
					shader->SetVector3(perfix + "direction", light->transform->Right());
					shader->SetVector3(perfix + "color", light->color);
					shader->SetFloat(perfix + "intensity", light->intensity);
				}

#ifdef NUWA_EDITOR
				shader->SetColor("gizmos.displayColor", Vector4(light->color, 1.0));
#endif // NUWA_EDITOR
			}
		}

	}

	void Material::AddLight(Light* light)
	{
		if (!light)
			return;
		if (!lights.count(light->type))
			lights[light->type] = std::unordered_set<Light*>();

		if (lights[light->type].count(light))
			return;

		lights[light->type].insert(light);
	}

	void Material::RemoveLight(Light* light)
	{
		if (!light || !lights.count(light->type))
			return;

		lights[light->type].erase(light);
	}

}