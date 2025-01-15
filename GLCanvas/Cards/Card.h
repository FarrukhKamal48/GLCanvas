#pragma once
#include <GLBox.h>

enum class CardType {
    None,
    ColorCard
};

class Card {
protected:
    Card(CardType type) : m_Type(type) {}
public:
    virtual ~Card() {}
    
    virtual void OnEvent(Event& event) = 0;
    virtual void OnUpdate(float dt) = 0;
    virtual void OnImGuiRender() = 0; 

    virtual void Drag(glm::vec3 delta) = 0;
    virtual void SetZDepth(float zdepth) = 0;
protected:
    CardType m_Type;
};
