#pragma once
#include <glbpch.h>
#include <GLBox.h>

class Card {
public:
    Card() {};
    virtual ~Card() {};

    virtual void OnEvent(Event& event) {};
    
    virtual void OnUpdate(float dt) {};
    virtual void OnRender() {};
    virtual void OnImGuiRender() {};
};
