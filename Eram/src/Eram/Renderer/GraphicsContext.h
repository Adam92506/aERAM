#pragma once

namespace Eram {

	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Unique<GraphicsContext> Create(void* window);
	};

}