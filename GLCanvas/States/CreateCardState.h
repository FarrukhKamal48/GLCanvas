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
        m_DropdownFinished = false;
        m_NewCardID = -1;
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
            static std::stringstream buttonLabel;
            buttonLabel.clear();
            buttonLabel << "New Color Card " << newCardType << "###" << newCardType;
            
            if (m_IsMenuSticky) {
                if (ImGui::Button(buttonLabel.str().c_str(), ImVec2(ImGui::GetContentRegionAvail().x, m_ButtonHeight))) {
                    m_NewCardID = CVData().Cardmanager->AddCard(newCardType, glm::vec3(CVData().WorldMousePos, 1.0f));
                    m_DropdownFinished = true;
                }
                
                static bool canCreateCard = true;
                if (ImGui::BeginDragDropSource()) {
                    if (canCreateCard) {
                        m_NewCardID = CVData().Cardmanager->AddCard(newCardType, glm::vec3(CVData().WorldMousePos, 1.0f));
                        canCreateCard = false;
                    }
                    if (CVData().Cardmanager->IsValid(m_NewCardID)) {
                        CVData().Cardmanager->Get(m_NewCardID).Drag(glm::vec3(CVData().WorldMouseDelta, 0.0f));
                    }
                    
                    ImGui::EndDragDropSource();
                }
                if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
                    canCreateCard = true;
                }
            }
            else {
                if (ImGui::Button(buttonLabel.str().c_str(), ImVec2(ImGui::GetContentRegionAvail().x, m_ButtonHeight)) || 
                    (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && ImGui::IsItemHovered())) {
                    m_NewCardID = CVData().Cardmanager->AddCard(newCardType, glm::vec3(CVData().WorldMousePos, 1.0f));
                    m_DropdownFinished = true;
                }
            }
        }
        
        ImGui::End();
        ImGui::PopStyleVar();
    }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if ((Input::MousePressed(Mouse::ButtonLeft) && !m_IsWindowFocused) || m_DropdownFinished || 
            (Input::MousePressed(Mouse::ButtonLeft) && Input::KeyPressed(Key::LeftAlt))) {
            return State::Idle;
        }
        return State::CreateCard;
    }
private:
    glm::vec2 m_MenuPos = {0,0};
    bool m_IsWindowFocused = true;
    bool m_DropdownFinished = false;
    const float m_ButtonHeight = 30;
    int32_t m_NewCardID = -1;

    bool m_IsMenuSticky = true;
};

}
