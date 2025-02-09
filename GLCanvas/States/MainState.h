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
    void OnUpdate(float dt) override {
        if (Input::MousePressed(Mouse::ButtonLeft) && !Input::KeyPressed(Key::LeftControl) && !CVData().Cardmanager->IsCardHovered()) {
            CVData().Cardmanager->ClearSelection();
        }
    } 
    void OnImGuiRender() override { }
    void OnExit() override { } 
    StateKey GetNextState() override { 
        if (Input::MousePressed(Mouse::ButtonLeft) && Input::KeyPressed(Key::LeftControl) && CVData().Cardmanager->IsCardHovered() && !glm::length(CVData().WorldMouseDelta)) {
            return StateType::ClickSelect;
        }
        if (Input::MousePressed(Mouse::ButtonLeft) && !Input::KeyPressed(Key::LeftAlt) && CVData().Cardmanager->IsCardHovered()) {
            if (CVData().Cardmanager->GetSelection().size() <= 1) {
                CVData().Cardmanager->ClearSelection();
                CVData().Cardmanager->ToggleSelection(CVData().Cardmanager->GetHoveredCard());
            }
            return StateType::DraggCard;
        }
        if (Input::MousePressed(Mouse::ButtonRight) && !CVData().Cardmanager->IsCardHovered()) {
            return StateType::CreateCard;
        }
        return StateType::Main;
    }
};

}
