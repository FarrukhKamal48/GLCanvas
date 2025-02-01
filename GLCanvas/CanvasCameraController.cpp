#include "GLCanvas/CanvasCameraController.h"

void CanvasCameraController::OnEvent(Event& event) {
    EventDispacher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
    if (!m_Paused) {
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScroll));
    }
}

void CanvasCameraController::OnResize(uint32_t width, uint32_t height) {
    m_AspectRatio = (float)width / height;
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

void CanvasCameraController::Translate(const glm::vec3& translation) { 
    if (!m_Paused) {
        m_Camera.SetPosition(m_Camera.GetPosition() + translation); 
    }
}

bool CanvasCameraController::OnWindowResize(WindowResizeEvent& event) {
    OnResize(event.GetWidth(), event.GetHeight());
    return false;
}
bool CanvasCameraController::OnMouseScroll(MouseScrolledEvent& event) {
    m_ZoomLevel -= event.GetYOffset() * 0.05f;
    m_ZoomLevel = std::max(0.1f, m_ZoomLevel);
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
}
