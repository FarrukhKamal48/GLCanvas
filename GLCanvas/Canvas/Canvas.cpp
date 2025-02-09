#include "GLCanvas/Base.h"
#include "GLCanvas/Canvas/Canvas.h"

#include "GLCanvas/States/MainState.h"
#include "GLCanvas/States/PanningState.h"
#include "GLCanvas/States/DraggCardState.h"
#include "GLCanvas/States/CreateCardState.h"
#include "States/MultiSelectState.h"

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

State* State::Create(StateKey type) {
    switch (type) {
        case StateType::Main: return new MainState();
        case StateType::Panning: return new PanningState();
        case StateType::DraggCard: return new DraggCardState();
        case StateType::CreateCard: return new CreateCardState();
        case StateType::MultiSelect: return new MultiSelectState();
    }
    return nullptr;
}

}
