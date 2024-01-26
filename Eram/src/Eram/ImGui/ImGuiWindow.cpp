#include "erpch.h"
#include "ImGuiWindow.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Eram/Core/Application.h"

namespace Eram
{

	ImGuiWindow::ImGuiWindow()
	{

	}

	void ImGuiWindow::Init()
	{
		ER_PROFILE_FUNCTION();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls

		ImGui::StyleColorsDark();

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiWindow::Shutdown()
	{
		ER_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiWindow::OnEvent(Event& e)
	{
		ER_PROFILE_FUNCTION();

		ImGuiIO& io = ImGui::GetIO();
		e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
		e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
	}

	void ImGuiWindow::Begin()
	{
		ER_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiWindow::End()
	{
		ER_PROFILE_FUNCTION();

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}