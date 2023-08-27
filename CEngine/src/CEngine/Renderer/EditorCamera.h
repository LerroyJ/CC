#pragma once

#include "Camera.h"
#include "CEngine/Core/Timestep.h"
#include "CEngine/Events/Event.h"
#include "CEngine/Events/MouseEvent.h"
#include <glm/glm.hpp>

namespace CEngine {
	class EditorCamera : public Camera {
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);
		bool OnMouseScroll(MouseScrolledEvent& e);

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;

		glm::vec3 GetForwardDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetUpDirection() const;

		glm::quat GetOrientation() const;

		void SetViewportSize(float width, float height) 
		{ 
			m_ViewportWidth = width;
			m_ViewportHeight = height; 
			UpdateProjection(); 
		}

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }
	private:
		void UpdateProjection();
		void UpdateView();

		glm::vec3 CalculatePosition() const;
	private:
		float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;
		glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_FocalPoint{ 0.0f,0.0f,0.0f };
		glm::vec2 m_InitialMousePosition{ 0.0f, 0.0f };

		float m_Distance = 10.0f;
		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		glm::mat4 m_ViewMatrix;

		float m_ViewportWidth = 1280, m_ViewportHeight = 720;
	};
}