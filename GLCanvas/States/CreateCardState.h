#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"
#include "GLCanvas/Base.h"
#include "imgui.h"

namespace Canvas {

class CreateCardState : public State {
public:
    CreateCardState() : State(StateType::CreateCard) {}
    ~CreateCardState() {}
    
    void OnEnter() override { 
        m_MenuPos = CVData().ImGuiMousePos; 
        m_NewCardID = -1;
        m_IsWindowFocused = true;
        m_DropdownFinished = false;
    }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { } 
    void OnImGuiRender() override { 
        IM::BeginStyleVars();
        IM::StyleVar(ImGuiStyleVar_WindowRounding, m_Styling.WindowRounding);
        IM::StyleVar(ImGuiStyleVar_ButtonTextAlign, m_Styling.ButtonTextAlign);
        IM::StyleVar(ImGuiStyleVar_FramePadding, m_Styling.FrameBadding);
        IM::StyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,1));
        
        ImGui::SetNextWindowPos(m_MenuPos);
        
        ImGui::Begin("##Card-Create", nullptr, 
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | 
            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings
        );
        
        m_IsWindowFocused = ImGui::IsWindowFocused();

        for (CardKey newCardType = CardType::None; newCardType < CardType::COUNT; newCardType++) {
            std::stringstream buttonLabel;
            buttonLabel << "New " << Card::TypeName(newCardType) << " Card";
            
            if (m_IsMenuSticky) {
                if (ImGui::Button(buttonLabel.str().c_str(), ImVec2(m_Styling.WindowWidth, m_Styling.ButtonHeight))) {
                    m_NewCardID = CVData().Cardmanager->AddCard(newCardType, glm::vec3(CVData().WorldMousePos, 1.0f));
                    m_DropdownFinished = true;
                }
                
                static bool canCreateCard = true;
                static bool* payloadPtr = nullptr;
                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceNoPreviewTooltip | ImGuiDragDropFlags_AcceptNoDrawDefaultRect)) {
                    if (canCreateCard) {
                        m_NewCardID = CVData().Cardmanager->AddCard(newCardType, glm::vec3(CVData().WorldMousePos, 1.0f));
                        canCreateCard = false;
                    }
                    if (CVData().Cardmanager->IsValid(m_NewCardID)) {
                        CVData().Cardmanager->Get(m_NewCardID).Drag(glm::vec3(CVData().WorldMouseDelta, 0.0f));
                    }
                    payloadPtr = &canCreateCard;
                    ImGui::SetDragDropPayload("CREATE_CARD_BOOL", &payloadPtr, sizeof(payloadPtr));
                    ImGui::EndDragDropSource();
                }
            }
            else {
                if (ImGui::Button(buttonLabel.str().c_str(), ImVec2(m_Styling.WindowWidth, m_Styling.ButtonHeight)) || 
                    (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && ImGui::IsItemHovered())) {
                    m_NewCardID = CVData().Cardmanager->AddCard(newCardType, glm::vec3(CVData().WorldMousePos, 1.0f));
                    m_DropdownFinished = true;
                }
            }
            
            IM::BeginStyleColors();
            IM::StyleColor(ImGuiCol_Separator, ImVec4(0.4,0.4,0.4,1.0));
            ImGui::Separator();
            IM::EndStyleColors();
        }
        
        ImGui::End();
        IM::EndStyleVars();
    }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if ((Input::MousePressed(Mouse::ButtonLeft) && !m_IsWindowFocused) || m_DropdownFinished || 
            (Input::MousePressed(Mouse::ButtonLeft) && Input::KeyPressed(Key::LeftAlt))) {
            return StateType::Idle;
        }
        return StateType::CreateCard;
    }
private:
    ImVec2 m_MenuPos = {0,0};
    int32_t m_NewCardID = -1;
    bool m_IsWindowFocused = true;
    bool m_DropdownFinished = false;

    bool m_IsMenuSticky = true;
    struct Styling {
        float WindowRounding = 5.0f;
        float WindowWidth = 200;
        float ButtonHeight = 30;
        ImVec2 ButtonTextAlign = {0.0,0.5};
        ImVec2 FrameBadding = {10,0};
    };
    Styling m_Styling;

};

}
