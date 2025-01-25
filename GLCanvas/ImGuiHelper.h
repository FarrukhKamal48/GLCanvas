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
