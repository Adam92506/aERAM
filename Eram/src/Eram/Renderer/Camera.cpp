#include "erpch.h"
#include "Camera.h"

#include "Eram/Core/Input.h"
#include "Eram/Core/KeyCodes.h"

#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Eram
{

	Camera::Camera()
		: m_FOV(45.0f), m_AspectRatio(1.778f), m_NearClip(0.1f), m_FarClip(1000.0f), m_Projection(glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip))
	{
		UpdateView();
	}

	Camera::Camera(glm::vec3 position, glm::vec3 rotation)
		: m_FOV(45.0f), m_AspectRatio(1.778f), m_NearClip(0.1f), m_FarClip(1000.0f), m_Projection(glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip)), m_Position(position), m_Rotation(rotation)
	{
		UpdateView();
	}

	Camera::Camera(float fov, float aspectRatio, float nearClip, float farClip)
		: m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip), m_Projection(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
	{
		UpdateView();
	}

	void Camera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
	}

	void Camera::UpdateView()
	{
		glm::quat orientation = GetOrientation();
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	glm::quat Camera::GetOrientation() const
	{
		return glm::quat(glm::radians(m_Rotation));
	}

}