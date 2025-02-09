#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class ClickSelectState : public State {
public:
    ClickSelectState() : State(StateType::ClickSelect) {}
    ~ClickSelectState() {}
    
    void OnEnter() override { 
        CVData().Cardmanager->ToggleSelection(CVData().Cardmanager->GetHoveredCard());
    }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { } 
    void OnImGuiRender() override { }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if (Input::MousePressed(Mouse::ButtonLeft) && Input::KeyPressed(Key::LeftControl) && CVData().Cardmanager->IsCardHovered() && !glm::length(CVData().WorldMouseDelta)) {
            return StateType::ClickSelect;
        }
        return StateType::Main;
    }
};

}
