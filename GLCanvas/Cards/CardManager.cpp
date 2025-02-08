#include "GLCanvas/Cards/CardManager.h"

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
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CREATE_CARD_BOOL")) {
            **(bool**)(payload->Data) = true;
        }
        ImGui::EndDragDropTarget();
    }
} 

uint32_t CardManager::AddCard(CardKey type, const glm::vec3& pos) {
    if (type == CardType::None)
        return -1;

    m_Cards.push_back(Card::Create(type, m_Cards.size(), pos));
    return m_Cards.size()-1;
}

void CardManager::RemoveCard(CardID cardID) {
    assert(IsValid(cardID) && "Invalid Card ID");
    m_Cards.erase(m_Cards.begin() + cardID);
}

void CardManager::RemoveSelection(CardID cardID) {
    auto it = std::find(m_Selection.begin(), m_Selection.end(), cardID);
    if (it != m_Selection.end()) {
        m_Selection.erase(it);
    }
}

bool CardManager::IsValid(int32_t cardID) const {
    return cardID != -1 && cardID >= 0 && cardID < (int32_t)m_Cards.size();
}

Card& CardManager::Get(CardID cardID) const {
    assert(IsValid(cardID) && "Invalid Card ID");
    return *m_Cards[cardID];
}

