#pragma once
#include <GLBox.h>

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
    OrthoCameraController* m_CameraController;
    glm::vec2 m_ViewportSize = { 0, 0 };
    glm::vec2 m_WorldMouseDelta = { 0, 0 };
    glm::vec2 m_WorldMousePos = { 0, 0 };
    ImVec2 m_WindowMousePos = { 0, 0 };
};
CanvasData& CVData();
glm::vec2 ScreenToWorld(ImVec2 screenCoords);
ImVec2 WorldToScreen(glm::vec2 worldCoords);

class BaseState {
public:
    BaseState(StateKey state) : m_State(state) {}
    virtual ~BaseState() {}
    StateKey GetState() { return m_State; }
    virtual void OnEnter() = 0;
    virtual void OnEvent(Event& event) = 0;
    virtual void OnUpdate(float dt) = 0;
    virtual void OnExit() = 0;
    virtual StateKey GetNextState() = 0;
protected:
    StateKey m_State;
};
