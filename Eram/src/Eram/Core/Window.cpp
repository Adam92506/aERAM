#include "erpch.h"
#include "Window.h"

#ifdef ER_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Eram
{

	Unique<Window> Window::Create(const WindowProps& props)
	{
		#ifdef ER_PLATFORM_WINDOWS
			return CreateUnique<WindowsWindow>(props);
		#else
			ER_ASSERT(false, "Renderer: No supported rendering API");
			return nullptr;
		#endif
	}

}