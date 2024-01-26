#include "erpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Eram
{

	Unique<RendererAPI> RendererAPI::Create()
	{
		#ifdef ER_PLATFORM_WINDOWS
			return CreateUnique<OpenGLRendererAPI>();
		#else
			ER_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

}