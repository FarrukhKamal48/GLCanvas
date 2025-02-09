#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class MainState : public State {
public:
    MainState() : State(StateType::Main) {}
    ~MainState() {}
    
    void OnEnter() override {  }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { } 
    void OnImGuiRender() override { }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if (Input::MousePressed(Mouse::ButtonLeft) && !Input::KeyPressed(Key::LeftAlt) && !Input::KeyPressed(Key::LeftControl) && CVData().Cardmanager->IsCardHovered()) {
            CVData().Cardmanager->ClearSelection();
            CVData().Cardmanager->AddSelection(CVData().Cardmanager->GetHoveredCard());
            return StateType::DraggCard;
        }
        if (Input::MousePressed(Mouse::ButtonRight) && !CVData().Cardmanager->IsCardHovered()) {
            return StateType::CreateCard;
        }
        return StateType::Main;
    }
};

}
