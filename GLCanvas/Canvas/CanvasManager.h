#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/Canvas.h"

namespace Canvas {

class CanvasManager {
public:
    CanvasManager();
    ~CanvasManager();
    
    void OnEvent(Event& event);
    void OnUpdate(float dt); 
    void OnRender(); 
    void OnCanvasRender(); 
private:
    std::vector<BaseState*> m_States;
    StateKey m_ActiveState = State::Idle;
    StateKey m_NextState = State::Idle;
    bool m_IsTransitioning = false;
};

}
