#pragma once

#include "Eram/Events/ApplicationEvent.h"
#include "Eram/Events/KeyEvent.h"
#include "Eram/Events/MouseEvent.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace Eram
{

	class ImGuiWindow
	{
	public:
		ImGuiWindow();
		~ImGuiWindow() = default;

		void Init();
		void Shutdown();
		void OnEvent(Event& e);

		void Begin();
		void End();
	};

}