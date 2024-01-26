#include "erpch.h"
#include "CameraController.h"

#include "Eram/Core/Input.h"

namespace Eram
{

	CameraController::CameraController()
		: m_Camera(m_CameraPosition, m_CameraRotation)
	{
		m_Camera.SetViewportSize(1280, 720);
	}

	CameraController::CameraController(float fov, float aspectRatio, float nearClip, float farClip)
		: m_Camera(fov, aspectRatio, nearClip, farClip) 
	{
		m_Camera.SetViewportSize(1280, 720);
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(ER_BIND_EVENT_FN(CameraController::OnWindowResizeEvent));
	}

	void CameraController::OnResize(float width, float height)
	{
		m_Camera.SetViewportSize(width, height);
	}

	void CameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Key::A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation.y)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.z += sin(glm::radians(m_CameraRotation.y)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation.y)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.z -= sin(glm::radians(m_CameraRotation.y)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::W))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation.y - 90.0f)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.z += sin(glm::radians(m_CameraRotation.y - 90.0f)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::S))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation.y - 90.0f)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.z -= sin(glm::radians(m_CameraRotation.y - 90.0f)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::X))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::Z))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::Q))
		{
			m_CameraRotation.y += m_CameraRotationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::E))
		{
			m_CameraRotation.y -= m_CameraRotationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::R))
		{
			m_CameraRotation.x += m_CameraRotationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::F))
		{
			m_CameraRotation.x -= m_CameraRotationSpeed * ts;
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
	}

	bool CameraController::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}