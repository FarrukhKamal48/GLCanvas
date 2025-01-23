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
    
    bool IsValid(int32_t cardID);
    Card& Get(CardID cardID);
    
    Card& operator[](CardID cardID) { return Get(cardID); }
private:
    std::vector<Card*> m_Cards;
};
