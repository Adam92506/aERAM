#include "erpch.h"
#include "CameraController.h"

#include "Eram/Core/Input.h"

namespace Eram {

	CameraController::CameraController(float width, float height, float zoomLevel, float rotation)
		: m_AspectRatio(width / height), m_Width(width), m_Height(height), m_ZoomLevel(zoomLevel), m_Rotation(rotation),
		m_Camera(m_AspectRatio * m_ZoomLevel, -m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
		m_Camera.SetPosition(m_Position);
		m_Camera.SetRotation(m_Rotation);
	}

	void CameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
		{
			if (m_PrevMousePressed)
			{
				glm::vec2 mousePosition = Input::GetMousePos();
				glm::vec2 deltaPosition = (m_PrevMousePosition - mousePosition);

				deltaPosition.x = deltaPosition.x * m_TranslationSpeed * ts * m_ZoomLevel;
				deltaPosition.y = deltaPosition.y * m_TranslationSpeed * ts * m_ZoomLevel;

				glm::mat4 viewProjection = m_Camera.GetViewProjectionMatrix();
				glm::vec4 position = glm::vec4(deltaPosition.x, deltaPosition.y, 0.0f, 0.0f) * viewProjection;

				m_Position += glm::vec3(position.x, -position.y, 0.0f);
				m_Camera.SetPosition(m_Position);

				m_PrevMousePosition = mousePosition;
				m_PrevMousePressed = true;
			}
			
			else
			{
				m_PrevMousePosition = Input::GetMousePos();
				m_PrevMousePressed = true;
			}
		}

		else
		{
			m_PrevMousePressed = false;
		}
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(ER_BIND_EVENT_FN(CameraController::OnWindowResized));
		dispatcher.Dispatch<MouseScrolledEvent>(ER_BIND_EVENT_FN(CameraController::OnMouseScrolled));
	}

	void CameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Width = width;
		m_Height = height;
		RecalculateProjection();
	}
	
	void CameraController::RecalculateProjection()
	{
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * m_ZoomSpeed;
		RecalculateProjection();

		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}