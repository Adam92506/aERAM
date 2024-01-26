#include "erpch.h"
#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Eram
{

	Ref<Texture2D> Texture2D::Create(Image& image)
	{
		#ifdef ER_PLATFORM_WINDOWS
			return CreateRef<OpenGLTexture2D>(image);
		#else
			ER_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		#ifdef ER_PLATFORM_WINDOWS
			return CreateRef<OpenGLTexture2D>(filepath);
		#else
			ER_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

}