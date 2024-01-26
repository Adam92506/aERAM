#include "erpch.h"
#include "OpenGLShader.h"

#include "Eram/Core/Log.h"
#include "Eram/Core/Core.h"
#include "Eram/Core/Timer.h"
#include "Eram/Utils/Utils.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Eram {

	namespace Utils
	{

		static GLenum ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")
				return GL_VERTEX_SHADER;
			if (type == "fragment" || type == "pixel")
				return GL_FRAGMENT_SHADER;

			ER_ASSERT(false, "Unknown shader type!");
			return 0;
		}

	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
		: m_Filepath(filepath)
	{
		
		ER_PROFILE_FUNCTION();

		// TODO: Not cause error when file does not exist

		ShaderSource source = PreProcess(filepath);
		CompileShader(source.VertexSource, source.FragmentSource);
		ER_INFO("Loaded '{0}' shader", filepath);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		ER_PROFILE_FUNCTION();

		CompileShader(vertexSrc, fragmentSrc);
		ER_INFO("Loaded '{0}' shader", name);
	}

	void OpenGLShader::CompileShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		ER_PROFILE_FUNCTION();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			ER_ERROR("{0}", infoLog.data());
			ER_ERROR("{0}", vertexSource.c_str());
			ER_ASSERT(false, "Vertex shader compilation failure");
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);

			ER_ERROR("{0}", infoLog.data());
			ER_ERROR("{0}", fragmentSource.c_str());
			ER_ASSERT(false, "Fragment shader compilation failure");
			return;
		}

		m_RendererID = glCreateProgram();

		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			ER_ERROR("{0}", infoLog.data());
			ER_ASSERT(false, "Shader link failure")

			return;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	ShaderSource OpenGLShader::PreProcess(const std::string& filepath)
	{
		ER_PROFILE_FUNCTION();

		std::ifstream stream(filepath);

		enum class ShaderType
		{
			None = -1, Vertex = 0, Fragment = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::None;
		while (std::getline(stream, line))
		{
			if (line.find("#type") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::Vertex;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::Fragment;
			}
			else
			{
				ss[(int)type] << line << "\n";
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	OpenGLShader::~OpenGLShader()
	{
		ER_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int32_t value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetInt2(const std::string& name, const glm::ivec2& value)
	{
		UploadUniformInt2(name, value);
	}

	void OpenGLShader::SetInt3(const std::string& name, const glm::ivec3& value)
	{
		UploadUniformInt3(name, value);
	}

	void OpenGLShader::SetInt4(const std::string& name, const glm::ivec4& value)
	{
		UploadUniformInt4(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int32_t* values, uint32_t count)
	{
		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetUInt(const std::string& name, uint32_t value)
	{
		UploadUniformUInt(name, value);
	}

	void OpenGLShader::SetUInt2(const std::string& name, const glm::uvec2& value)
	{
		UploadUniformUInt2(name, value);
	}

	void OpenGLShader::SetUInt3(const std::string& name, const glm::uvec3& value)
	{
		UploadUniformUInt3(name, value);
	}

	void OpenGLShader::SetUInt4(const std::string& name, const glm::uvec4& value)
	{
		UploadUniformUInt4(name, value);
	}

	void OpenGLShader::SetUIntArray(const std::string& name, uint32_t* values, uint32_t count)
	{
		UploadUniformUIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		UploadUniformFloat2(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetFloatArray(const std::string& name, float* values, uint32_t count)
	{
		UploadUniformFloatArray(name, values, count);
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& value)
	{
		UploadUniformMat3(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMat4(name, value);
	}


	void OpenGLShader::UploadUniformInt(const std::string& name, int32_t value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformInt2(const std::string& name, const glm::ivec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2i(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformInt3(const std::string& name, const glm::ivec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3i(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformInt4(const std::string& name, const glm::ivec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4i(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int32_t* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformUInt(const std::string& name, uint32_t value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1ui(location, value);
	}

	void OpenGLShader::UploadUniformUInt2(const std::string& name, const glm::uvec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2ui(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformUInt3(const std::string& name, const glm::uvec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3ui(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformUInt4(const std::string& name, const glm::uvec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4ui(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformUIntArray(const std::string& name, uint32_t* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1uiv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformFloatArray(const std::string& name, float* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1fv(location, count, values);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

}