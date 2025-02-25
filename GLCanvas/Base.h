#pragma once
#include <GLBox.h>


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

template<typename T>
T Lerp(const T& A, const T& B, float t) {
    return A + (B - A) * t;
}


namespace IM {


static std::vector<int32_t> styleVarCounts = {};
static std::vector<int32_t> styleColCounts = {};

inline void BeginStyleVars() {
    styleVarCounts.emplace_back(0);
}
inline void StyleVar(ImGuiStyleVar idx, const ImVec2& val) {
    styleVarCounts.back()++;
    ImGui::PushStyleVar(idx, val);
}
inline void StyleVar(ImGuiStyleVar idx, float val) {
    styleVarCounts.back()++;
    ImGui::PushStyleVar(idx, val);
}
inline void EndStyleVars() {
    ImGui::PopStyleVar(styleVarCounts.back());
    styleVarCounts.pop_back();
}


inline void BeginStyleColors() {
    styleColCounts.emplace_back(0);
}
inline void StyleColor(ImGuiCol idx, ImU32 col) {
    styleColCounts.back()++;
    ImGui::PushStyleColor(idx, col);
}

inline void StyleColor(ImGuiCol idx, const ImVec4& col) {
    styleColCounts.back()++;
    ImGui::PushStyleColor(idx, col);
}

inline void EndStyleColors() {
    ImGui::PopStyleColor(styleColCounts.back());
    styleColCounts.pop_back();
}

inline bool IsMouseOverWindow() {
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    return mousePos.x >= windowPos.x && mousePos.x <= windowPos.x + viewportSize.x
        && mousePos.y >= windowPos.y && mousePos.y <= windowPos.y + viewportSize.y;
}

}
