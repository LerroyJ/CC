#include "ccpch.h"
#include "CameraController.h"
#include "CEngine/Core/Input.h"
#include "CEngine/Core/keyCodes.h"
namespace CEngine {
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    {

    }
    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
		if (CEngine::Input::IsKeyPressed(KeyCode::A)) {
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (CEngine::Input::IsKeyPressed(KeyCode::D)) {
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		if (CEngine::Input::IsKeyPressed(KeyCode::W)) {
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (CEngine::Input::IsKeyPressed(KeyCode::S)) {
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		if (m_Rotation)
		{
			if (CEngine::Input::IsKeyPressed(KeyCode::Q)) {
				m_CameraRotation += m_CameraRotationSpeed * ts.GetSecond();
			}
			else if (CEngine::Input::IsKeyPressed(KeyCode::E)) {
				m_CameraRotation -= m_CameraRotationSpeed * ts.GetSecond();
			}

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}
		
		
		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
    }
    void OrthographicCameraController::OnEvent(Event& event)
    {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    }
    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
    {
		m_ZoomLevel -= event.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
    {
        OnResize((float)event.GetWidth(), (float)event.GetHeight());
		return false;
    }

	void OrthographicCameraController::OnResize(float width, float height) {
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	// ----------------------------------------------------------------------------------------------------
	// PerspectiveCamera
	// ----------------------------------------------------------------------------------------------------


	PerspectiveCameraController::PerspectiveCameraController(float aspectRatio) 
		: m_AspectRatio(aspectRatio), m_Camera(aspectRatio)
	{
		
	}
	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		if (CEngine::Input::IsKeyPressed(KeyCode::W)) {
			m_Camera.ProcessKeyboard(PerspectiveCamera::FORWARD, ts);
		}
		else if (CEngine::Input::IsKeyPressed(KeyCode::S)) {
			m_Camera.ProcessKeyboard(PerspectiveCamera::BACKWARD, ts);
		}

		if (CEngine::Input::IsKeyPressed(KeyCode::A)) {
			m_Camera.ProcessKeyboard(PerspectiveCamera::LEFT, ts);
		}
		else if (CEngine::Input::IsKeyPressed(KeyCode::D)) {
			m_Camera.ProcessKeyboard(PerspectiveCamera::RIGHT, ts);
		}
	}
	void PerspectiveCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
	}
	void PerspectiveCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(m_AspectRatio);
	}
	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_Camera.ProcessMouseScroll(event.GetYOffset());
		return false;
	}
	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& event)
	{
		OnResize((float)event.GetWidth(), (float)event.GetHeight());
		return false;
	}
}