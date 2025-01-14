#pragma once
#include <GLBox.h>
#include "Cards/CardObject.h"
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

static bool IsValid(int32_t id) {
    return id != -1 && id >= 0 && id < (int32_t)CardTransform_Manager().m_Instances.size();
}

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
        else if (Input::MousePressed(Mouse::ButtonLeft) && IsValid(CVData().HoveredCardID)) {
            return State::DraggCard;
        }
        return State::Idle;
    }
};

}
