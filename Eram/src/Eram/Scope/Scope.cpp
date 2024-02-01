#include "erpch.h"
#include "Scope.h"

#include "Eram/Core/Application.h"

#include "Eram/Renderer/Renderer.h"
#include "Eram/ImGui/ImGuiWindow.h"

#include "Eram/Core/Input.h"

namespace Eram
{

	Scope::Scope()
		: m_CameraController(1280, 720, 10.0f, 0.0f)
	{

	}

	Scope::~Scope()
	{

	}

	void Scope::Init()
	{
		m_VideoMap = VideoMap("Eram/assets/HIGH AIRWAYS.geojson");
		m_VideoMap2 = VideoMap("Eram/assets/ZNY - High Sectors.geojson");
	}

	void Scope::Free()
	{

	}

	void Scope::OnUpdate(Timestep ts)
	{
		m_CameraController.OnUpdate(ts);

		RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		RenderCommand::Clear();

		Renderer::BeginScene(m_CameraController.GetCamera());

		m_VideoMap.Draw();
		m_VideoMap2.Draw();

		#ifdef ER_DEBUG
		uint32_t drawCalls = Renderer::GetDrawCallCount();
		uint32_t quadCount = Renderer::GetQuadCount();
		uint32_t lineCount = Renderer::GetLineCount();
		#endif 

		Renderer::EndScene();

		ImGui::Begin("Debug Window");

		glm::vec2 mousePosition = Input::GetMousePos();
		ImGui::Text("Mouse Position: %.3f, %.3f", mousePosition.x, mousePosition.y);

		glm::vec2 cameraPosition = m_CameraController.GetCamera().GetPosition();
		ImGui::Text("Camera Position: %.3f, %.3f", cameraPosition.x, cameraPosition.y);

		ImGui::Text("Zoom Level: %.1f", m_CameraController.GetZoomLevel());

		ImGui::SliderFloat("Rotation", &m_Rotation, 0.0f, 360.0f);
		m_CameraController.SetRotation(m_Rotation);

		#ifdef ER_DEBUG
		ImGui::Text("Draw Calls: %d", drawCalls);
		ImGui::Text("Quad Count: %d", quadCount);
		ImGui::Text("Line Count: %d", lineCount);
		#endif 

		ImGui::End();
	}

	void Scope::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);
	}

}