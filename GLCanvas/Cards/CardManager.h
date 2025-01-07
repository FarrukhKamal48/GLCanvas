#pragma once
#include <glbpch.h>

#include "GLCanvas/Cards/Card.h"

class CardManager {
public:
    CardManager() = default;
    ~CardManager() {
        for (Card* card : m_Cards) {
            delete card;
        }
    }

    void AddCard(Card* card) {
        m_Cards.push_back(card);
    }
    void RemoveCard(Card* card) {
        auto it = std::find(m_Cards.begin(), m_Cards.end(), card);
        if (it != m_Cards.end()) {
            m_Cards.erase(it);
            delete it.base();
        }
    }

private:   
    std::vector<Card*> m_Cards;
};
