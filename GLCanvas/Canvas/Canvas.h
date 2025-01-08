#pragma once
#include <glbpch.h>
#include <GLBox.h>

#include "GLCanvas/Cards/CardManager.h"


class Canvas {
public:    
    Canvas();
    ~Canvas();
    
    void OnEvent(Event& event);
    void OnAttach();
    void OnUpdate(float dt);
    void OnImGuiRender();

    void OnViewportResize(glm::vec2 size);

    OrthoCameraController& GetCameraController() { return m_CameraController; }
    glm::vec2 GetWorldMousePos() { return m_WorldMousePos; }
    ImVec2 GetWindowMousePos() { return m_WindowMousePos; }
    const glm::vec2& GetViewportSize() { return m_ViewportSize; }

    glm::vec2 ScreenToWorld(ImVec2 screenCoords);
    ImVec2 WorldToScreen(glm::vec2 worldCoords);

private:
    OrthoCameraController m_CameraController;
    
    CardManager m_CardManager;
    
    QuadTransform_Manager m_Manager;
    uint32_t m_BackgroundI = -1;
    
    glm::vec2 m_ViewportSize = { 0, 0 };
    glm::vec2 m_WorldMouseDelta = { 0, 0 };
    glm::vec2 m_WorldMousePos = { 0, 0 };
    ImVec2 m_WindowMousePos = { 0, 0 };
};
