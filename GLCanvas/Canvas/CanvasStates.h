#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/State.h"

namespace CanvasState {
    enum : FSMKey {
        Idle,
        Panning,
        DraggCard,
        DraggSelect,
        MAX,
    };
}

struct FSMData {
    OrthoCameraController& m_CameraController;
    glm::vec2 m_ViewportSize = { 0, 0 };
    glm::vec2 m_WorldMouseDelta = { 0, 0 };
    glm::vec2 m_WorldMousePos = { 0, 0 };
    ImVec2 m_WindowMousePos = { 0, 0 };
};

class IdleState : public State {
public:
    IdleState(FSMKey state, FSMData& data) : State(state, data) {}
    ~IdleState() {}
    
    void OnEnter() override { BASIC_LOG("Idle"); }
    void OnEvent(Event& event) override {} 
    void OnUpdate(float dt) override { } 
    void OnExit() override {} 
    FSMKey GetNextState() override { 
        if (Input::KeyPressed(Key::Space))
            return CanvasState::Panning; 
        return CanvasState::Idle;
    }
};

class PanningState : public State {
public:
    PanningState(FSMKey state, FSMData& data) : State(state, data) {}
    ~PanningState() {}
    
    void OnEnter() override { BASIC_LOG("Panning"); }
    void OnEvent(Event& event) override {} 
    void OnUpdate(float dt) override { } 
    void OnExit() override {} 
    FSMKey GetNextState() override { 
        if (Input::KeyPressed(Key::Enter))
            return CanvasState::Idle; 
        return CanvasState::Panning;
    }
};
