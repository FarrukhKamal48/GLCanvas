#pragma once
#include <GLBox.h>

namespace IM {

static int32_t styleVarCount = 0;
static int32_t styleColCount = 0;

inline void PushStyleVar(ImGuiStyleVar idx, const ImVec2& val) {
    styleVarCount++;
    ImGui::PushStyleVar(idx, val);
}
inline void PushStyleVar(ImGuiStyleVar idx, float val) {
    styleVarCount++;
    ImGui::PushStyleVar(idx, val);
}
inline void PopStyleVars() {
    ImGui::PopStyleVar(styleVarCount);
    styleVarCount = 0;
}

inline void PushStyleColor(ImGuiCol idx, ImU32 col) {
    styleColCount++;
    ImGui::PushStyleColor(idx, col);
}

inline void PushStyleColor(ImGuiCol idx, const ImVec4& col) {
    styleColCount++;
    ImGui::PushStyleColor(idx, col);
}

inline void PopStyleColors() {
    ImGui::PopStyleColor(styleColCount);
    styleColCount = 0;
}

}


inline bool operator!=(ImVec2 A, glm::vec2 B) { return A.x!=B.x || A.y!=B.y; }
inline bool operator!=(glm::vec2 A, ImVec2 B) { return A.x!=B.x || A.y!=B.y; }
inline bool operator!=(ImVec2 A, ImVec2 B) { return A.x!=B.x || A.y!=B.y; }

// inline ImVec2 operator+(glm::vec2 A, glm::vec2 B) { return {A.x+B.x, A.y+B.y}; }
inline ImVec2 operator+(ImVec2 A, glm::vec2 B) { return {A.x+B.x, A.y+B.y}; }
inline ImVec2 operator+(glm::vec2 A, ImVec2 B) { return {A.x+B.x, A.y+B.y}; }
inline ImVec2 operator+(ImVec2 A, ImVec2 B) { return {A.x+B.x, A.y+B.y}; }

// inline ImVec2 operator-(glm::vec2 A, glm::vec2 B) { return {A.x-B.x, A.y-B.y}; }
inline ImVec2 operator-(ImVec2 A, glm::vec2 B) { return {A.x-B.x, A.y-B.y}; }
inline ImVec2 operator-(glm::vec2 A, ImVec2 B) { return {A.x-B.x, A.y-B.y}; }
inline ImVec2 operator-(ImVec2 A, ImVec2 B) { return {A.x-B.x, A.y-B.y}; }

// inline ImVec2 operator*(glm::vec2 A, glm::vec2 B) { return {A.x*B.x, A.y*B.y}; }
inline ImVec2 operator*(ImVec2 A, glm::vec2 B) { return {A.x*B.x, A.y*B.y}; }
inline ImVec2 operator*(glm::vec2 A, ImVec2 B) { return {A.x*B.x, A.y*B.y}; }
inline ImVec2 operator*(ImVec2 A, ImVec2 B) { return {A.x*B.x, A.y*B.y}; }

// inline ImVec2 operator/(glm::vec2 A, glm::vec2 B) { return {A.x/B.x, A.y/B.y}; }
inline ImVec2 operator/(ImVec2 A, glm::vec2 B) { return {A.x/B.x, A.y/B.y}; }
inline ImVec2 operator/(glm::vec2 A, ImVec2 B) { return {A.x/B.x, A.y/B.y}; }
inline ImVec2 operator/(ImVec2 A, ImVec2 B) { return {A.x/B.x, A.y/B.y}; }

inline ImVec2 operator*(ImVec2 A, float val) { return {A.x*val, A.y*val}; }
inline ImVec2 operator*(ImVec2 A, int val) { return {A.x*val, A.y*val}; }

inline ImVec2 operator/(ImVec2 A, float val) { return {A.x/val, A.y/val}; }
inline ImVec2 operator/(ImVec2 A, int val) { return {A.x/val, A.y/val}; }

