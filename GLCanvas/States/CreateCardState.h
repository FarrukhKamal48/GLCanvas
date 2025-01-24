#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class CreateCardState : public BaseState {
public:
    CreateCardState() : BaseState(State::CreateCard) {}
    ~CreateCardState() {}
    
    void OnEnter() override { 
        m_MenuPos = CVData().WorldMousePos; 
        m_DropdownFinished = false;
    }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { } 
    void OnImGuiRender() override { 
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
        
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

        for (CardKey newCardType = CardType::None; newCardType < CardType::MAX; newCardType++) {
            std::stringstream buttonLabel;
            buttonLabel << "New Color Card " << newCardType << "###" << newCardType;
            
            if (m_IsMenuSticky) {
                if (ImGui::Button(buttonLabel.str().c_str(), ImVec2(ImGui::GetContentRegionAvail().x, m_ButtonHeight))) {
                    m_NewCardID = CVData().Cardmanager->AddCard(newCardType, glm::vec3(CVData().WorldMousePos, 1.0f));
                    m_DropdownFinished = true;
                }
                
                static bool isNewCardCreated = false;
                if (ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                    if (!isNewCardCreated) {
                        m_NewCardID = CVData().Cardmanager->AddCard(newCardType, glm::vec3(CVData().WorldMousePos, 1.0f));
                        isNewCardCreated = true;
                    }
                    if (CVData().Cardmanager->IsValid(m_NewCardID)) {
                        CVData().Cardmanager->Get(m_NewCardID).Drag(glm::vec3(CVData().WorldMouseDelta, 0.0f));
                    }
                }
                else {
                    isNewCardCreated = false;
                }
            }
            else {
                if (ImGui::Button(buttonLabel.str().c_str(), ImVec2(ImGui::GetContentRegionAvail().x, m_ButtonHeight)) || 
                    (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && ImGui::IsItemHovered())) {
                    CVData().Cardmanager->AddCard(newCardType, glm::vec3(CVData().WorldMousePos, 1.0f));
                    m_DropdownFinished = true;
                }
            }
        }
        
        ImGui::End();
        ImGui::PopStyleVar();
    }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if ((Input::MousePressed(Mouse::ButtonLeft) && !m_IsWindowFocused) || m_DropdownFinished) {
            return State::Idle;
        }
        return State::CreateCard;
    }
private:
    glm::vec2 m_MenuPos = {0,0};
    bool m_IsWindowFocused = true;
    bool m_DropdownFinished = false;
    const float m_ButtonHeight = 30;
    CardID m_NewCardID = -1;

    bool m_IsMenuSticky = true;
};

}
