#include "erpch.h"
#include "GraphicsContext.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Eram
{

	Unique<GraphicsContext> GraphicsContext::Create(void* window)
	{
		#ifdef ER_PLATFORM_WINDOWS
			return CreateUnique<OpenGLContext>(static_cast<GLFWwindow*>(window));
		#else
			ER_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

}