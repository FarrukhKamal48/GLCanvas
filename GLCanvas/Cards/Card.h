#pragma once
#include <glbpch.h>
#include <GLBox.h>

class Card {
public:
    Card() {};
    virtual ~Card() {};

    void SetMousePos(glm::vec2 pos) { m_WorldMousePos = pos; }
    void SetMouseDelta(glm::vec2 delta) { m_WorldMouseDelta = delta; }
    static bool IsHovered(glm::vec2 bottomleft, glm::vec2 topright, glm::vec2 mouse) { 
        return mouse.x >= bottomleft.x && mouse.x <= topright.x && 
               mouse.y >= bottomleft.y && mouse.y <= topright.y;
    }

    virtual void OnEvent(Event& event) {};
    
    virtual void OnUpdate(float dt) {};
    virtual void OnRender() {};
    virtual void OnImGuiRender() {};
protected:
    glm::vec2 m_WorldMousePos;
    glm::vec2 m_WorldMouseDelta;
};
