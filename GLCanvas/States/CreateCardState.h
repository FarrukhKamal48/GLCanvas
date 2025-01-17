#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"
#include "imgui.h"

namespace Canvas {

class CreateCardState : public BaseState {
public:
    CreateCardState() : BaseState(State::CreateCard) {}
    ~CreateCardState() {}
    
    void OnEnter() override { 
        m_MenuPos = CVData().WorldMousePos; 
        m_ButtonClicked = false;
    }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { } 
    void OnImGuiRender() override { 
        ImGui::SetNextWindowPos(WorldToScreen(m_MenuPos));
        ImGui::SetNextWindowSize(ImVec2(200,250));
        ImGui::Begin("###Card-Create", nullptr, 
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse | 
            ImGuiWindowFlags_AlwaysAutoResize | 
            ImGuiWindowFlags_NoSavedSettings
        );
        m_IsWindowFocused = ImGui::IsWindowFocused();
        
        if (ImGui::Button("New Color", ImVec2(ImGui::GetContentRegionAvail().x, m_ButtonHeight))) {
            CVData().Cardmanager->AddCard(CardType::ColorCard, glm::vec3(CVData().WorldMousePos, 1.0f), glm::vec4(0,1,0,1));
            m_ButtonClicked = true;
        }

        ImGui::End();
    }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if ((Input::MousePressed(Mouse::ButtonLeft) && !m_IsWindowFocused) || m_ButtonClicked) {
            return State::Idle;
        }
        return State::CreateCard;
    }
private:
    glm::vec2 m_MenuPos = {0,0};
    bool m_IsWindowFocused = true;
    bool m_ButtonClicked = false;
    const float m_ButtonHeight = 20;
};

}
