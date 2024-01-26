#include "erpch.h"
#include "VertexArray.h"

#ifdef ER_PLATFORM_WINDOWS
#include "Platform/OpenGL/OpenGLVertexArray.h"
#endif

namespace Eram {

	Ref<VertexArray> VertexArray::Create()
	{
		#ifdef ER_PLATFORM_WINDOWS
			return CreateRef<OpenGLVertexArray>();
		#else
			ER_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

}