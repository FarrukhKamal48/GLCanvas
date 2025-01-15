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
private:
    std::vector<BaseState*> m_States;
    StateKey m_ActiveState = State::Idle;
    bool m_IsTransitioning = false;

    CardManager m_CardManger;
};

}
