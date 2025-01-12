#include "GLCanvas/Cards/CardManager.h"

bool CardManager::IsValidateID(uint32_t id) {
    return id != m_InvalidID && id >= 0 && id < m_Cards.size();
}
