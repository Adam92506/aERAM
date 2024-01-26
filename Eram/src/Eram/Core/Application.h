#pragma once

#include "Core.h"

#include "Eram/Events/Event.h"
#include "Eram/Events/ApplicationEvent.h"

#include "Window.h"

#include "Eram/ImGui/ImGuiWindow.h"
#include "Eram/Scope/Scope.h"

namespace Eram {

	class Application
	{
	public:
		Application();
		~Application();

		void OnEvent(Event& e);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Unique<Window> m_Window;

		Ref<Scope> m_Scope;
		Ref<ImGuiWindow> m_ImGuiWindow;

		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

}