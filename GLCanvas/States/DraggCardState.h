#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class DraggCardState : public State {
public:
    DraggCardState() : State(StateType::DraggCard) {}
    ~DraggCardState() {}
    
    void OnEnter() override { 
        m_CurrCardID = CVData().HoveredCardID;
        if (m_LastCardID != -1 && m_CurrCardID != -1) {
            CVData().Cardmanager->Get(m_CurrCardID).SetZDepth(1);
            CVData().Cardmanager->Get(m_LastCardID).SetZDepth(0);
        }
    }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { 
        CVData().Cardmanager->Get(m_CurrCardID).Drag(glm::vec3(CVData().WorldMouseDelta, 0.0f));
        CVData().Cardmanager->Get(m_CurrCardID).SetZDepth(1.0f);
    } 
    void OnImGuiRender() override { }
    void OnExit() override { 
        m_LastCardID = m_CurrCardID;
    } 
    StateKey GetNextState() override { 
        if (Input::MouseReleased(Mouse::ButtonLeft) || Input::KeyPressed(Key::LeftAlt))
            return StateType::Idle;
        return StateType::DraggCard;
    }
private:
    int32_t m_CurrCardID = -1;
    int32_t m_LastCardID = -1;
};

}
