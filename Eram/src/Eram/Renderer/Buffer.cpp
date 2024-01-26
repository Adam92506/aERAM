#include "erpch.h"
#include "Buffer.h"

#ifdef ER_PLATFORM_WINDOWS
#include "Platform/OpenGL/OpenGLBuffer.h"
#endif

namespace Eram {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		#ifdef ER_PLATFORM_WINDOWS
			return CreateRef<OpenGLVertexBuffer>(size);
		#else
			ER_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

	Ref<VertexBuffer> VertexBuffer::Create(void* verticies, uint32_t size)
	{
		#ifdef ER_PLATFORM_WINDOWS
			return CreateRef<OpenGLVertexBuffer>(verticies, size);
		#else
			ER_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indecies, uint32_t count)
	{
		#ifdef ER_PLATFORM_WINDOWS
			return CreateRef<OpenGLIndexBuffer>(indecies, count);
		#else
			ER_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

}