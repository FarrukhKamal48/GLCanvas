#pragma once
#include <glbpch.h>
#include <GLBox.h>

#include "GLCanvas/Cards/Card.h"

class CardManager {
public:
    CardManager() = default;
    ~CardManager() = default;

    void OnEvent(Event& event);
    void OnUpdate(float dt); 
    void OnImGuiRender(); 

    CardID AddCard(CardKey type, const glm::vec3& pos);
    void RemoveCard(CardID cardID); 

    void SetHoveredCard(int32_t cardID) { m_HoveredCard = cardID; }
    int32_t GetHoveredCard() { return m_HoveredCard; };
    bool IsCardHovered() { return IsValid(m_HoveredCard); }
    
    bool IsValid(int32_t cardID);
    Card& Get(CardID cardID);
    
    Card& operator[](CardID cardID) { return Get(cardID); }
private:
    std::vector<Card*> m_Cards;
    int32_t m_HoveredCard = -1;
};
