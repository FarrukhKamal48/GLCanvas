#include "GLCanvas/Canvas/CanvasCameraController.h"
#include "GLCanvas/Base.h"
#include "GLCanvas/Canvas/Canvas.h"

void CanvasCameraController::OnEvent(Event& event) {
    EventDispacher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
    dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScroll));
}

void CanvasCameraController::OnResize(uint32_t width, uint32_t height) {
    m_AspectRatio = (float)width / height;
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

void CanvasCameraController::OnUpdate(float dt) {
    if (m_IsLocked) {
        return;
    }
    if (Input::MousePressed(Mouse::ButtonLeft) && Input::KeyPressed(Key::LeftAlt)) {
        m_Camera.SetPosition(m_Camera.GetPosition() 
                             - glm::vec3(Canvas::CVData().WorldMouseDelta, 0.0f));
    }
}

void CanvasCameraController::Translate(const glm::vec3& translation) { 
    if (m_IsLocked) {
        return;
    }
    m_Camera.SetPosition(m_Camera.GetPosition() + translation); 
}

bool CanvasCameraController::OnWindowResize(WindowResizeEvent& event) {
    OnResize(event.GetWidth(), event.GetHeight());
    return false;
}

bool CanvasCameraController::OnMouseScroll(MouseScrolledEvent& event) {
    if (m_IsLocked) {
        return false;
    }
    float oldZoom = m_ZoomLevel;
    m_ZoomLevel -= event.GetYOffset() * 0.05f;
    m_ZoomLevel = std::max(0.1f, m_ZoomLevel - event.GetYOffset() * 0.05f);
    
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    m_Camera.SetPosition(Lerp(
        m_Camera.GetPosition(), 
        glm::vec3(Canvas::CVData().WorldMousePos, 0), 
        -(m_ZoomLevel - oldZoom)/oldZoom
    ));
    return false;
}
