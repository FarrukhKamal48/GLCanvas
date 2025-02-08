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
    void OnImGuiRender() override { }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if (!Input::KeyPressed(Key::LeftAlt) && Input::MousePressed(Mouse::ButtonLeft) && CVData().Cardmanager->IsCardHovered()) {
            return StateType::DraggCard;
        }
        if (Input::MousePressed(Mouse::ButtonRight) && !CVData().Cardmanager->IsCardHovered()) {
            return StateType::CreateCard;
        }
        return StateType::Idle;
    }
};

}
