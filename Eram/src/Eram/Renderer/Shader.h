#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Eram {

	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int32_t value) = 0;
		virtual void SetInt2(const std::string& name, const glm::ivec2& value) = 0;
		virtual void SetInt3(const std::string& name, const glm::ivec3& value) = 0;
		virtual void SetInt4(const std::string& name, const glm::ivec4& value) = 0;
		virtual void SetIntArray(const std::string& name, int32_t* values, uint32_t count) = 0;

		virtual void SetUInt(const std::string& name, uint32_t value) = 0;
		virtual void SetUInt2(const std::string& name, const glm::uvec2& value) = 0;
		virtual void SetUInt3(const std::string& name, const glm::uvec3& value) = 0;
		virtual void SetUInt4(const std::string& name, const glm::uvec4& value) = 0;
		virtual void SetUIntArray(const std::string& name, uint32_t* values, uint32_t count) = 0;

		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetFloatArray(const std::string& name, float* values, uint32_t count) = 0;

		virtual void SetMat3(const std::string & name, const glm::mat3& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}