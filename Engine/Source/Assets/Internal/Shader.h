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

		std::unordered_map<std::string, i32> m_UniformLocations;

	private:
		i32 m_ProgramId = 0;
		i32 m_VertexShaderId = 0;
		i32 m_FragmentShaderId = 0;

	private:
		Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
		~Shader() = default;

	private:
		void Init();
		void Free();

	private:
		void LinkProgram(RenderBackend& renderBackend);
		static i32 CompileShader(const std::string& shaderPath, ShaderType type, RenderBackend& renderBackend);
		static std::string ReadShaderFile(const std::string& filePath);

	private:
		void LoadUniformLocations(RenderBackend& renderBackend);
		i32 GetUniformLocation(const std::string& name) const;

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
