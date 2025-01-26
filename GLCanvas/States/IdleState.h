#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class IdleState : public State {
public:
    IdleState() : State(StateType::Idle) {}
    ~IdleState() {}
    
    void OnEnter() override {  }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { } 
    void OnImGuiRender() override {
        m_IsCanvasHovered = ImGui::GetIO().WantCaptureMouse;
        BASIC_LOG(m_IsCanvasHovered);
    }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if (Input::MousePressed(Mouse::ButtonLeft) && Input::KeyPressed(Key::LeftAlt) && m_IsCanvasHovered) {
            return StateType::Panning;
        }
        else if (Input::MousePressed(Mouse::ButtonLeft) && CVData().Cardmanager->IsValid(CVData().HoveredCardID)) {
            return StateType::DraggCard;
        }
        if (Input::MousePressed(Mouse::ButtonRight) && !CVData().Cardmanager->IsValid(CVData().HoveredCardID) && m_IsCanvasHovered) {
            return StateType::CreateCard;
        }
        return StateType::Idle;
    }
private:
    bool m_IsCanvasHovered = false;
};

}
