#include "erpch.h"
#include "Shader.h"

#ifdef ER_PLATFORM_WINDOWS
#include "Platform/OpenGL/OpenGLShader.h"
#endif

namespace Eram {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		#ifdef ER_PLATFORM_WINDOWS
			return CreateRef<OpenGLShader>(filepath);
		#else
			ER_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		#ifdef ER_PLATFORM_WINDOWS
			return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		#else
			ER_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

}