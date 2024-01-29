#pragma once

#include "Eram/Renderer/Camera.h"

#include "Eram/Core/Timestep.h"

#include "Eram/Events/ApplicationEvent.h"
#include "Eram/Events/MouseEvent.h"

namespace Eram {

	class CameraController
	{
	public:
		CameraController(float width, float height, float zoomLevel, float rotation);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		void RecalculateProjection();

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; RecalculateProjection(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; m_Camera.SetRotation(rotation); }
	private:
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		Camera m_Camera;

		float m_AspectRatio;
		float m_Width, m_Height;
		float m_ZoomLevel;

		float m_Rotation;
		glm::vec3 m_Position = { 40.74488780507533f, -74.24515365415176f, 0.0f };
		glm::vec2 m_PrevMousePosition = {0.0f, 0.0f};
		bool m_PrevMousePressed = false;

		float m_TranslationSpeed = 500.0f;
	};

}