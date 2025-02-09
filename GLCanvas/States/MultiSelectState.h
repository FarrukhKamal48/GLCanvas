#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class MultiSelectState : public State {
public:
    MultiSelectState() : State(StateType::MultiSelect) {}
    ~MultiSelectState() {}
    
    void OnEnter() override { }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { } 
    void OnImGuiRender() override { }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        return StateType::Main;
    }
};

}
