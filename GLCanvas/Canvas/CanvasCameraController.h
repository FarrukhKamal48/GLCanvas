#pragma once
#include <GLBox.h>

class CanvasCameraController {
public:
    CanvasCameraController(float aspectRatio, float zoomLevel, bool paused)
        : m_AspectRatio(aspectRatio), m_ZoomLevel(zoomLevel), m_IsLocked(paused)
        , m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    { }

    void OnEvent(Event& event);
    void OnResize(uint32_t width, uint32_t height);
    void OnUpdate(float dt);
    
    void Translate(const glm::vec3& translation);
    void Lock(bool locked) { m_IsLocked = locked; }

    OrthoCamera& GetCamera()        { return m_Camera; } 
    float GetAspectRatio()          { return m_AspectRatio; }
    float GetZoomLevel()            { return m_ZoomLevel; }
    const glm::vec2& GetBounds()    { return m_Camera.GetBounds(); }
private:
    bool OnWindowResize(WindowResizeEvent& event);
    bool OnMouseScroll(MouseScrolledEvent& event);
private:
    float m_AspectRatio = 16.0f/9.0f;
    float m_ZoomLevel = 1.0f;
    bool m_IsLocked = false;
    OrthoCamera m_Camera;
};
