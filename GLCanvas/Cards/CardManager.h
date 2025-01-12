#pragma once
#include <glbpch.h>

class Card;

class CardManager {
public:
    CardManager();
    ~CardManager();
private:    
    std::vector<Card*> m_Cards;
    bool IsValidateID(uint32_t id);
    const int32_t m_InvalidID = -1;
};
