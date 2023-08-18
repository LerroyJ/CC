#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
namespace CEngine {
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0,0.0,0.0 };
		float m_Rotation = 0.0f;
	};

	class PerspectiveCamera {
	public:
		enum Camera_Movement {
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT,
			UP,
			DOWN
		};
		PerspectiveCamera(float aspectRatio, glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.f, float pitch = 0.0f);

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void SetProjection(float aspectRatio);
		void ProcessKeyboard(Camera_Movement direction, float ts);
		void ProcessMouseScroll(float yoffset);
	private:
		void UpdateCameraVectors();
		void CalculateMatrix(float aspectRatio);
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	private:
		// camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		// euler Angles
		float Yaw;
		float Pitch;
		// camera options
		float MovementSpeed = 2.5f;
		float MouseSensitivity = 0.1f;
		float Zoom = 45.0f;
		// camera perspective
		float Near;
		float Far;
		float AspectRatio;
	};

	class Camera {
	public:
		Camera(const glm::mat4& projection) : m_Projection(projection) {}
		const glm::mat4& GetProjection() const { return m_Projection; }
	private:
		glm::mat4 m_Projection;
	};
}