#include "GLCanvas/Cards/CardManager.h"
#include "GLCanvas/Canvas/Canvas.h"

void CardManager::OnEvent(Event& event) {
    for (auto [cardID, cardptr]: m_Cards) {
        cardptr->OnEvent(event);
    }
}
void CardManager::OnUpdate(float dt) {
    for (auto [cardID, cardptr]: m_Cards) {
        cardptr->OnUpdate(dt);
    }
} 
void CardManager::OnImGuiRender() { 
    for (auto [cardID, cardptr]: m_Cards) {
        cardptr->OnImGuiRender();
    }
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CREATE_CARD_BOOL")) {
            **(bool**)(payload->Data) = true;
        }
        ImGui::EndDragDropTarget();
    }
    // just for debugging
    for (CardID ID : m_Selection) {
        ImGui::GetWindowDrawList()->AddCircleFilled(
            Canvas::WorldToScreen(m_Cards[ID]->GetPosition()),
            10, 
            IM_COL32(55, 255, 35, 255)
        );
    }
} 

uint32_t CardManager::AddCard(CardKey type, const glm::vec3& pos) {
    if (type == CardType::None)
        return -1;

    CardID cardID = m_Cards.size();
    Card* cardptr = Card::Create(type, m_Cards.size(), pos);
    m_Cards.insert(std::make_pair(cardID, cardptr));
    return cardID;
}

void CardManager::RemoveCard(CardID cardID) {
    assert(IsValid(cardID) && "Invalid Card ID");
    if (m_Cards.count(cardID)) {
        m_Cards.erase(cardID);
    }
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

Card& CardManager::Get(CardID cardID) {
    assert(IsValid(cardID) && "Invalid Card ID");
    return *m_Cards[cardID];
}

