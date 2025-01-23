#pragma once
#include <glbpch.h>
#include <GLBox.h>

#include "GLCanvas/Cards/Card.h"
#include "GLCanvas/Cards/ColorCard.h"

class CardManager {
public:
    CardManager() = default;
    ~CardManager() = default;

    void OnEvent(Event& event);
    void OnUpdate(float dt); 
    void OnImGuiRender(); 

    void AddCard(CardKey type, const glm::vec3& pos) {
        switch (type) {
            case CardType::None: break;
            case CardType::ColorCard: {
                m_Cards.push_back(new ColorCard(m_Cards.size(), pos)); 
                break;
            }
        }
    }
    void RemoveCard(uint32_t cardID); 
    
    bool IsValid(int32_t cardID);
    Card& Get(uint32_t cardID);
    
    Card& operator[](uint32_t cardID) { return Get(cardID); }
private:
    std::vector<Card*> m_Cards;
};
