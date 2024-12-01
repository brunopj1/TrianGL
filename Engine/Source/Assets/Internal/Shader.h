#pragma once

#include <Core/DataTypes.h>
#include <Core/Services/Backends/RenderBackend.h>
#include <string>
#include <unordered_map>

namespace TGL
{
	class Shader final
	{
	private:
		friend class AssetManager;
		friend class Material;
		friend class MaterialUniform;
		friend class SpriteUniform;
		friend struct ShaderHash;
		friend struct ShaderEqual;

	private:
		std::string m_VertexShader;
		std::string m_FragmentShader;

		std::vector<ShaderAttributeInfo> m_Attributes;
		std::unordered_map<std::string, ShaderUniformInfo> m_Uniforms;

	private:
		i32 m_ProgramId = 0;

	private:
		Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
		~Shader() = default;

	private:
		const std::vector<ShaderAttributeInfo>& GetAttributes() const;
		i32 GetUniformLocation(const std::string& name) const;
		ShaderDataType GetUniformDataType(const std::string& name) const;

	private:
		void Init();
		void Free();

	private:
		void LinkProgram(RenderBackend& renderBackend, u32 vertexShaderId, u32 fragmentShaderId);
		static i32 CompileShader(const std::string& shaderPath, ShaderType type, RenderBackend& renderBackend);
		static std::string ReadShaderFile(const std::string& filePath);

	private:
		void LoadAttributes(RenderBackend& renderBackend);
		void LoadUniformLocations(RenderBackend& renderBackend);

	private:
		void Use() const;
	};

	struct ShaderHash
	{
		std::size_t operator()(const Shader* shader) const;
	};

	struct ShaderEqual
	{
		bool operator()(const Shader* shader1, const Shader* shader2) const;
	};
}
