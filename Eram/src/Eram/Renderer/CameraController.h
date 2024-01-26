#pragma once

#include "Camera.h"

#include "Eram/Core/Timestep.h"

#include "Eram/Events/ApplicationEvent.h"
#include "Eram/Events/KeyEvent.h"

namespace Eram
{

	class CameraController
	{
	public:
		CameraController();
		CameraController(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		glm::vec3 GetPosition() const { return m_CameraPosition; }

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		float GetFOV() const { return m_Camera.GetFOV(); }
		void SetFOV(float fov) { m_Camera.SetFOV(fov); }
	private:
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		glm::vec3 m_CameraPosition = { 0.0f, 70.0f, 0.0f };
		glm::vec3 m_CameraRotation = { 0.0f, 180.0f, 0.0f };

		float m_CameraTranslationSpeed = 10.0f, m_CameraRotationSpeed = 90.0f;

		Camera m_Camera;
	};
	
}