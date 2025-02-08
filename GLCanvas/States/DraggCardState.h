#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class DraggCardState : public State {
public:
    DraggCardState() : State(StateType::DraggCard) {}
    ~DraggCardState() {}
    
    void OnEnter() override { }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { 
        for (CardID ID : CVData().Cardmanager->GetSelection()) {
            CVData().Cardmanager->Get(ID).Drag(glm::vec3(CVData().WorldMouseDelta, 0.0f));
        }
    } 
    void OnImGuiRender() override { }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if (Input::MouseReleased(Mouse::ButtonLeft) || Input::KeyPressed(Key::LeftAlt))
            return StateType::Main;
        return StateType::DraggCard;
    }
};

}
