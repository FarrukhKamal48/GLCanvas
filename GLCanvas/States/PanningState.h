#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class PanningState : public State {
public:
    PanningState() : State(StateType::Panning) {}
    ~PanningState() {}
    
    void OnEnter() override { }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override {
        CVData().Camera->Translate(-glm::vec3(CVData().WorldMouseDelta, 0.0f));
    } 
    void OnImGuiRender() override { }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if (Input::MouseReleased(Mouse::ButtonLeft) || Input::KeyReleased(Key::LeftAlt))
            return StateType::Main;
        return StateType::Panning;
    }
};

}
