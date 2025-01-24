#pragma once
#include <GLBox.h>

typedef uint32_t CardKey;
namespace CardType {
    enum : uint32_t {
        None,
        ColorCard,
        MAX,
    };
}

typedef uint32_t CardID;

class Card {
protected:
    Card(CardKey type, CardID id) : m_Type(type), m_CardID(id) {}
public:
    virtual ~Card() {}
    
    virtual void OnEvent(Event& event) = 0;
    virtual void OnUpdate(float dt) = 0;
    virtual void OnImGuiRender() = 0; 

    virtual void Drag(glm::vec3 delta) = 0;
    virtual void SetZDepth(float zdepth) = 0;
protected:
    CardKey m_Type;
    CardID m_CardID;
};
