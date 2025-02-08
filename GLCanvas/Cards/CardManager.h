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
    int32_t GetHoveredCard() const { return m_HoveredCard; };
    bool IsCardHovered() const { return IsValid(m_HoveredCard); }

    void AddSelection(CardID cardID) { m_Selection.push_back(cardID); }
    void RemoveSelection(CardID cardID);
    void ClearSelection() { m_Selection.clear(); }
    const std::vector<CardID>& GetSelection() const { return m_Selection; }
    
    bool IsValid(int32_t cardID) const;
    Card& Get(CardID cardID) const;
    
    Card& operator[](CardID cardID) const { return Get(cardID); }
private:
    std::vector<Card*> m_Cards;
    std::vector<CardID> m_Selection;
    int32_t m_HoveredCard = -1;
};
