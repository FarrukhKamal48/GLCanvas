#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"
#include "GLCanvas/Cards/CardManager.h"

namespace Canvas {

class CanvasManager {
public:
    CanvasManager();
    ~CanvasManager();
    
    void OnEvent(Event& event);
    void OnUpdate(float dt); 
    void OnRender(); 
    void OnImGuiRender(); 

    void TransitionTo(StateKey nextState);
    void Lock(bool locked) { m_IsLocked = locked; }
private:
    std::vector<State*> m_States;
    StateKey m_ActiveState = StateType::Idle;
    bool m_IsTransitioning = false;
    bool m_IsLocked = false;

    CardManager m_CardManger;
};

}
