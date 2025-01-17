#include "GLCanvas/Canvas/Canvas.h"
#include "GLCanvas/ImVec2Defines.h"

namespace Canvas {
static CanvasData s_CVData;

CanvasData& CVData() { return s_CVData; }

glm::vec2 ScreenToWorld(ImVec2 screenCoords) {
    return glm::vec2(
        screenCoords.x/s_CVData.ViewportSize.x - 0.5f,
        1.0f - screenCoords.y/s_CVData.ViewportSize.y - 0.5f
    ) * s_CVData.Camera->GetBounds() + glm::vec2(s_CVData.Camera->GetCamera().GetPosition());
}

ImVec2 WorldToScreen(glm::vec2 worldCoords) {
    return glm::vec2(
        0.5f + (worldCoords.x - s_CVData.Camera->GetCamera().GetPosition().x)/s_CVData.Camera->GetBounds().x,
        0.5f - (worldCoords.y - s_CVData.Camera->GetCamera().GetPosition().y)/s_CVData.Camera->GetBounds().y
    ) * s_CVData.ViewportSize + ImGui::GetWindowPos() + glm::vec2(0, ImGui::GetWindowHeight() - s_CVData.ViewportSize.y);
}

}
