#pragma once
#include <GLBox.h>

typedef uint32_t CardKey;
namespace CardType {
    enum : uint32_t {
        None,
        ColorCard
    };
}

class Card {
protected:
    Card(CardKey type) : m_Type(type) {}
public:
    virtual ~Card() {}
    
    virtual void OnEvent(Event& event) = 0;
    virtual void OnUpdate(float dt) = 0;
    virtual void OnImGuiRender() = 0; 

    virtual void Drag(glm::vec3 delta) = 0;
    virtual void SetZDepth(float zdepth) = 0;
protected:
    CardKey m_Type;
};
