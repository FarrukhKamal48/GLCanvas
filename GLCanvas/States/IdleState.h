#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class IdleState : public BaseState {
public:
    IdleState(StateKey state) : BaseState(state) {}
    ~IdleState() {}
    
    void OnEnter() override { BASIC_LOG("Idle"); }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { } 
    void OnImGuiRender() override { }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if (Input::KeyPressed(Key::Space))
            return State::Panning; 
        return State::Idle;
    }
};

}
