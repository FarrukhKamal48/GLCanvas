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
        m_CardOrgZdepth = m_CardAllocator[m_CurrHoveredID].position.z;
    }
    void OnEvent(Event& event) override { } 
    void OnUpdate(float dt) override { 
        m_CardAllocator[m_CurrHoveredID].position += glm::vec3(CVData().WorldMouseDelta, 0.0f);
        m_CardAllocator[m_CurrHoveredID].position.z = 1.0f;
    } 
    void OnImGuiRender() override { }
    void OnExit() override { 
        m_CardAllocator[m_CurrHoveredID].position.z = m_CardOrgZdepth;
    } 
    StateKey GetNextState() override { 
        if (Input::MouseReleased(Mouse::ButtonLeft) || Input::KeyPressed(Key::LeftAlt))
            return State::Idle;
        return State::DraggCard;
    }
private:
    uint32_t m_CurrHoveredID = -1;
    float m_CardOrgZdepth = 0.0f;
    CardTransform_Manager m_CardAllocator;
};

}
