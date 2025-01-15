#pragma once
#include <GLBox.h>

namespace Canvas {

typedef uint32_t StateKey;
namespace State {
    enum : StateKey {
        Idle,
        Panning,
        DraggCard,
        DraggSelect,
        MAX,
    };
}

struct CanvasData {
    OrthoCameraController* Camera;
    int32_t HoveredCardID = -1;
    glm::vec2 ViewportSize = { 0, 0 };
    glm::vec2 WorldMouseDelta = { 0, 0 };
    glm::vec2 WorldMousePos = { 0, 0 };
    ImVec2 WindowMousePos = { 0, 0 };
};
CanvasData& CVData();
glm::vec2 ScreenToWorld(ImVec2 screenCoords);
ImVec2 WorldToScreen(glm::vec2 worldCoords);

class BaseState {
protected:
    BaseState(StateKey state) : m_State(state) {}
public:
    virtual ~BaseState() {}
    const StateKey GetState() { return m_State; }
    virtual void OnEnter() = 0;
    virtual void OnEvent(Event& event) = 0;
    virtual void OnUpdate(float dt) = 0;
    virtual void OnExit() = 0;
    virtual void OnImGuiRender() = 0;
    virtual StateKey GetNextState() = 0;
protected:
    const StateKey m_State;
};

}
