#include "GLCanvas/Cards/CardManager.h"
#include "GLCanvas/Cards/ColorCard.h"

void CardManager::OnEvent(Event& event) {
    for (Card* card : m_Cards) {
        card->OnEvent(event);
    }
}
void CardManager::OnUpdate(float dt) {
    for (Card* card : m_Cards) {
        card->OnUpdate(dt);
    }
} 
void CardManager::OnImGuiRender() { 
    for (Card* card : m_Cards) {
        card->OnImGuiRender();
    }
} 

uint32_t CardManager::AddCard(CardKey type, const glm::vec3& pos) {
    switch (type) {
        case CardType::None: return -1;
        case CardType::ColorCard: {
            m_Cards.push_back(new ColorCard(m_Cards.size(), pos)); 
            return m_Cards.size()-1;
        }
    }
    return -1;
}

void CardManager::RemoveCard(CardID cardID) {
    assert(IsValid(cardID) && "Invalid Card ID");
    m_Cards.erase(m_Cards.begin() + cardID);
}

bool CardManager::IsValid(int32_t cardID) {
    return cardID != -1 && cardID >= 0 && cardID < (int32_t)m_Cards.size();
}

Card& CardManager::Get(CardID cardID) {
    assert(IsValid(cardID) && "Invalid Card ID");
    return *m_Cards[cardID];
}

