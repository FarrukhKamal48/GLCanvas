#include "GLCanvas/Cards/Card.h"
#include "GLCanvas/Cards/ColorCard.h"

static const char* CardTypeTOName[CardType::COUNT] = {
    "None Card",
    "Color Card",
};

const char* Card::TypeName(CardKey type) {
    if (type == CardType::COUNT) {
        return "Unknown Card";
    }
    return CardTypeTOName[type];
}

Card* Card::Create(CardKey type, CardID cardID, const glm::vec3& pos) {
    switch (type) {
        case CardType::ColorCard: return new ColorCard(cardID, pos);
    }
    return nullptr;
}

