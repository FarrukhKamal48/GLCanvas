#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class PanningState : public BaseState {
public:
    PanningState(StateKey state) : BaseState(state) {}
    ~PanningState() {}
    
    void OnEnter() override { BASIC_LOG("Panning"); }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { } 
    void OnImGuiRender() override { }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if (Input::KeyPressed(Key::Enter))
            return State::Idle; 
        return State::Panning;
    }
};

}
