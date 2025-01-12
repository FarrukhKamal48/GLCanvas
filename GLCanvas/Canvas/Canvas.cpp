#include "GLCanvas/Canvas/Canvas.h"
#include "GLCanvas/ImVec2Defines.h"

namespace Canvas {
static CanvasData s_CVData;

CanvasData& CVData() { return s_CVData; }

glm::vec2 ScreenToWorld(ImVec2 screenCoords) {
    return glm::vec2(
        screenCoords.x/CVData().ViewportSize.x - 0.5f,
        1.0f - screenCoords.y/CVData().ViewportSize.y - 0.5f
    ) * CVData().Camera->GetBounds() + glm::vec2(CVData().Camera->GetCamera().GetPosition());
}

ImVec2 WorldToScreen(glm::vec2 worldCoords) {
    return glm::vec2(
        0.5f + (worldCoords.x - CVData().Camera->GetCamera().GetPosition().x)/CVData().Camera->GetBounds().x,
        0.5f - (worldCoords.y - CVData().Camera->GetCamera().GetPosition().y)/CVData().Camera->GetBounds().y
    ) * CVData().ViewportSize + ImGui::GetWindowPos() + glm::vec2(0, ImGui::GetWindowHeight() - CVData().ViewportSize.y);
}

}
