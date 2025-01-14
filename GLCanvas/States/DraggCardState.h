#pragma once
#include <GLBox.h>
#include "Cards/CardObject.h"
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class DraggCardState : public BaseState {
public:
    DraggCardState() : BaseState(State::DraggCard) {}
    ~DraggCardState() {}
    
    void OnEnter() override { 
        m_CurrHoveredID = CVData().HoveredCardID;
        if (m_LastHoveredID != -1 && m_CurrHoveredID != -1) {
            m_CardAllocator[m_CurrHoveredID].position.z = 1;
            m_CardAllocator[m_LastHoveredID].position.z = 0;
        }
    }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { 
        m_CardAllocator[m_CurrHoveredID].position += glm::vec3(CVData().WorldMouseDelta, 0.0f);
        m_CardAllocator[m_CurrHoveredID].position.z = 1.0f;
    } 
    void OnImGuiRender() override { }
    void OnExit() override { 
        m_LastHoveredID = m_CurrHoveredID;
    } 
    StateKey GetNextState() override { 
        if (Input::MouseReleased(Mouse::ButtonLeft) || Input::KeyPressed(Key::LeftAlt))
            return State::Idle;
        return State::DraggCard;
    }
private:
    uint32_t m_CurrHoveredID = -1;
    uint32_t m_LastHoveredID = -1;
    CardTransform_Manager m_CardAllocator;
};

}
