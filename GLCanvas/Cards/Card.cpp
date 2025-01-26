#include "GLCanvas/Cards/Card.h"
#include "GLCanvas/Cards/ColorCard.h"

const char* Card::TypeName(CardKey type) {
    switch (type) {
        case CardType::ColorCard : return "Color Card";
    }
    return "Unknown Card";
}

Card* Card::Create(CardKey type, CardID cardID, const glm::vec3& pos) {
    switch (type) {
        case CardType::ColorCard: return new ColorCard(cardID, pos);
    }
    return nullptr;
}

