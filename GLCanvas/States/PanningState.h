#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class PanningState : public BaseState {
public:
    PanningState() : BaseState(State::Panning) {}
    ~PanningState() {}
    
    void OnEnter() override { BASIC_LOG("Panning"); }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override {
        CVData().Camera->Translate(-glm::vec3(CVData().WorldMouseDelta, 0.0f));
    } 
    void OnImGuiRender() override { }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if (Input::MouseReleased(Mouse::ButtonLeft) || Input::KeyReleased(Key::LeftAlt))
            return State::Idle;
        return State::Panning;
    }
};

}
