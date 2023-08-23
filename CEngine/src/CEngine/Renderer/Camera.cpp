#include "ccpch.h"
#include "Camera.h"

namespace CEngine {
	// ----------------------------------------------------------------------------------------------------
	// OrthographicCamera
	// ----------------------------------------------------------------------------------------------------

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1))
			* glm::translate(glm::mat4(1.0f), m_Position);


		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	// ----------------------------------------------------------------------------------------------------
	// PerspectiveCamera
	// ----------------------------------------------------------------------------------------------------

	PerspectiveCamera::PerspectiveCamera(float aspectRatio, glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		: Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch),
		Near(0.1f), Far(100.0f), Zoom(45.0f), AspectRatio(aspectRatio),
		MouseSensitivity(0.1f), MovementSpeed(2.5f)
	{
		UpdateCameraVectors();
		CalculateMatrix(aspectRatio);
	}

	void PerspectiveCamera::UpdateCameraVectors() {
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}

	void PerspectiveCamera::SetProjection(float aspectRatio) {
		AspectRatio = aspectRatio;
		m_ProjectionMatrix = glm::perspective(glm::radians(Zoom), aspectRatio, Near, Far);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::ProcessKeyboard(Camera_Movement direction, float ts)
	{
		float velocity = MovementSpeed * ts;
		if (direction == FORWARD)
			Position += Front * velocity;
		else if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		else if (direction == RIGHT)
			Position += Right * velocity;
		m_ViewMatrix = glm::lookAt(Position, Position + Front, Up);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::ProcessMouseScroll(float yoffset)
	{
		Zoom -= (float)yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
		m_ProjectionMatrix = glm::perspective(glm::radians(Zoom), AspectRatio, Near, Far);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::CalculateMatrix(float aspectRatio) {
		AspectRatio = aspectRatio;
		m_ViewMatrix = glm::lookAt(Position, Position + Front, Up);
		m_ProjectionMatrix = glm::perspective(glm::radians(Zoom), AspectRatio, Near, Far);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}