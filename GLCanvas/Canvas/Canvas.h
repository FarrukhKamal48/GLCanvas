#pragma once
#include <GLBox.h>
#include "GLCanvas/Cards/CardManager.h"
#include "GLCanvas/Canvas/CanvasCameraController.h"

namespace Canvas {

typedef uint32_t StateKey;
namespace StateType {
    enum : StateKey {
        Main,
        Panning,
        DraggCard,
        CreateCard,
        MultiSelect,
        SelectionBox,
        COUNT,
    };
}

struct CanvasData {
    CanvasCameraController* Camera;
    CardManager* Cardmanager;
    glm::vec2 ViewportSize = { 0, 0 };
    glm::vec2 WorldMouseDelta = { 0, 0 };
    glm::vec2 WorldMousePos = { 0, 0 };
    ImVec2 WindowMousePos = { 0, 0 };
    ImVec2 ImGuiMousePos = { 0, 0 };
};
CanvasData& CVData();
glm::vec2 ScreenToWorld(ImVec2 screenCoords);
ImVec2 WorldToScreen(glm::vec2 worldCoords);

class State {
protected:
    State(StateKey state) : m_State(state) {}
public:
    virtual ~State() {}
    const StateKey GetState() { return m_State; }
    virtual void OnEnter() = 0;
    virtual void OnEvent(Event& event) = 0;
    virtual void OnUpdate(float dt) = 0;
    virtual void OnExit() = 0;
    virtual void OnImGuiRender() = 0;
    virtual StateKey GetNextState() = 0;

    static State* Create(StateKey type);
protected:
    const StateKey m_State;
};

}
