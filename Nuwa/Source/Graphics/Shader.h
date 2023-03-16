#pragma once
#include "IBindable.h"
#include <string>
#include <unordered_map>


namespace Nuwa
{
	class Shader : public IBindable
	{
	public:
		Shader(const std::string& filepath);
		Shader(const std::unordered_map<ShaderType, std::string> paths);
		Shader(const std::string& vertFilePath, const std::string& fragFilePath);
		virtual ~Shader();

		//template<typename T>
		//T GetValue(const std::string& name);
		//template<typename T>
		//void SetValue(const std::string& name, T value);

		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetVector3(const std::string& name, Vector3 value);

		void SetColor(const std::string& name, Vector4 color);
		void SetColor(const std::string& name, Vector3 color);

		void SetMatrix4x4(const std::string& name, Matrix4x4 mat);

		int GetInt(const std::string& name) const;
		Vector3 GetColor(const std::string& name) const;

		bool HasUniform(const std::string& name);
		bool HasUniformBlock(const std::string& name);

		int GetUniformBlockIndex(const std::string& blockName) const;

		void BindBlock(const std::string& blockName, const uint bindingPoint);

		// Inherited via IBindable
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Clear() override;

		inline std::vector<std::string> Filepaths() const { return filepaths; }

		inline uint id() { return rendererID; }

	private:
		std::vector<std::string> filepaths;
		mutable std::unordered_map<std::string, int> uniformLocationMap;
		mutable std::unordered_map<std::string, int> uniformBlockLocationMap;

		ShaderSource Parse();
		uint CreateShader(const ShaderSource& source);
		uint CreateShader(const std::string& vertex, const std::string& fragment);
		uint Compile(uint type, const std::string& source);
		void Link(uint program);
		void Validate(uint program);
		int GetUniformLocation(const std::string& name) const;		
	};
}

