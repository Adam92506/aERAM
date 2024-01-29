#include "erpch.h"
#include "Application.h"

#include "Timer.h"
#include "Timestep.h"

#include "Eram/Utils/Utils.h"

#include "Eram/Renderer/Renderer.h"

namespace Eram
{
	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		ER_PROFILE_FUNCTION();

		ER_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(ER_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiWindow = CreateRef<ImGuiWindow>();
		m_ImGuiWindow->Init();

		m_Scope = CreateRef<Scope>();
		m_Scope->Init();

		this->Run();
	}

	Application::~Application()
	{
		m_Scope->Free();

		ER_PROFILE_FUNCTION();
	}

	void Application::OnEvent(Event& e)
	{
		ER_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ER_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(ER_BIND_EVENT_FN(Application::OnWindowResize));

		m_ImGuiWindow->OnEvent(e);
		m_Scope->OnEvent(e);
	}

	void Application::Run()
	{
		ER_PROFILE_FUNCTION();

		while (m_Running)
		{
			float time = Time::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_ImGuiWindow->Begin();

			m_Scope->OnUpdate(timestep);

			m_ImGuiWindow->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		ER_PROFILE_FUNCTION();

		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		ER_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}


}