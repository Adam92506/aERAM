#pragma once

#include "Eram/Core/Timestep.h"

#include "Eram/Events/Event.h"
#include "Eram/Events/MouseEvent.h"

#include <glm/glm.hpp>

namespace Eram
{

	class Camera
	{
	public:
		Camera();
		Camera(glm::vec3 position, glm::vec3 rotation);
		Camera(float fov, float aspectRatio, float nearClip, float farClip);

		inline void SetViewportSize(float width, float height) { m_ViewportWidth = width, m_ViewportHeight = height; UpdateProjection(); }

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }
		const glm::mat4& GetProjection() const { return m_Projection; }

		glm::quat GetOrientation() const;

		void SetPosition(glm::vec3 position) { m_Position = position; UpdateView(); }
		const glm::vec3& GetPosition() const { return m_Position; }

		void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; UpdateView(); }
		const glm::vec3& GetRotation() const { return m_Rotation; }

		void SetFOV(float fov) { m_FOV = fov; UpdateProjection(); }
		float GetFOV() const { return m_FOV; }
	private:
		void UpdateProjection();
		void UpdateView();
	private:
		float m_FOV = 70.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;

		glm::mat4 m_Projection = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix;
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };

		float m_ViewportWidth = 1280, m_ViewportHeight = 720;
	};

}