#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"
#include "GLCanvas/ImGuiHelper.h"

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
        IM::PushStyleVar(ImGuiStyleVar_WindowRounding, m_Styling.WindowRounding);
        IM::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, m_Styling.ButtonTextAlign);
        IM::PushStyleVar(ImGuiStyleVar_FramePadding, m_Styling.FrameBadding);
        IM::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,1));
        
        ImGui::SetNextWindowPos(WorldToScreen(m_MenuPos));
        ImGui::SetNextWindowSize(m_Styling.WindowSize);
        
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
            buttonLabel << "New Color Card " << newCardType;
            
            if (m_IsMenuSticky) {
                if (ImGui::Button(buttonLabel.str().c_str(), ImVec2(ImGui::GetContentRegionAvail().x, m_Styling.ButtonHeight))) {
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
                if (ImGui::Button(buttonLabel.str().c_str(), ImVec2(ImGui::GetContentRegionAvail().x, m_Styling.ButtonHeight)) || 
                    (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && ImGui::IsItemHovered())) {
                    m_NewCardID = CVData().Cardmanager->AddCard(newCardType, glm::vec3(CVData().WorldMousePos, 1.0f));
                    m_DropdownFinished = true;
                }
            }
            
            IM::PushStyleColor(ImGuiCol_Separator, ImVec4(0.4,0.4,0.4,1.0));
            ImGui::Separator();
            IM::PopStyleColors();
        }
        
        ImGui::End();
        IM::PopStyleVars();
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
    int32_t m_NewCardID = -1;

    bool m_IsMenuSticky = true;
    struct Styling {
        float WindowRounding = 5.0f;
        ImVec2 WindowSize = {200,250};
        float ButtonHeight = 30;
        ImVec2 ButtonTextAlign = {0.0,0.5};
        ImVec2 FrameBadding = {10,0};
    };
    Styling m_Styling;

};

}
