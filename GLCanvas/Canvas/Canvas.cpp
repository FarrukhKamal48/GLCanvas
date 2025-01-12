#include "GLCanvas/Canvas/Canvas.h"
#include "GLCanvas/ImVec2Extend.h"

static CanvasData s_CVData;

CanvasData& CVData() { return s_CVData; }

glm::vec2 ScreenToWorld(ImVec2 screenCoords) {
    return glm::vec2(
        screenCoords.x/CVData().m_ViewportSize.x - 0.5f,
        1.0f - screenCoords.y/CVData().m_ViewportSize.y - 0.5f
    ) * CVData().m_CameraController->GetBounds() + glm::vec2(CVData().m_CameraController->GetCamera().GetPosition());
}

ImVec2 WorldToScreen(glm::vec2 worldCoords) {
    return glm::vec2(
        0.5f + (worldCoords.x - CVData().m_CameraController->GetCamera().GetPosition().x)/CVData().m_CameraController->GetBounds().x,
        0.5f - (worldCoords.y - CVData().m_CameraController->GetCamera().GetPosition().y)/CVData().m_CameraController->GetBounds().y
    ) * CVData().m_ViewportSize + ImGui::GetWindowPos() + glm::vec2(0, ImGui::GetWindowHeight() - CVData().m_ViewportSize.y);
}
