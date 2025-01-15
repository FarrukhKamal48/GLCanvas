#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class IdleState : public BaseState {
public:
    IdleState() : BaseState(State::Idle) {}
    ~IdleState() {}
    
    void OnEnter() override { }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { } 
    void OnImGuiRender() override { }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if (Input::MousePressed(Mouse::ButtonLeft) && Input::KeyPressed(Key::LeftAlt)) {
            return State::Panning;
        }
        else if (Input::MousePressed(Mouse::ButtonLeft) && CVData().Cardmanager->IsValid(CVData().HoveredCardID)) {
            return State::DraggCard;
        }
        return State::Idle;
    }
};

}
