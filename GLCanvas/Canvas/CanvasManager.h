#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/States.h"
#include "GLCanvas/ImVec2Extend.h"

class CanvasManager {
public:
    CanvasManager(StateKey startState) 
        : m_ActiveState(startState), m_NextState(startState) 
    {
        m_States.reserve(State::MAX);
        m_States[State::Idle] = new IdleState(State::Idle);
        m_States[State::Panning] = new PanningState(State::Panning);
        m_States[m_ActiveState]->OnEnter();
    }
    ~CanvasManager() {
        for (BaseState* state : m_States) {
            delete state;
        }
    }
    
    void OnEvent(Event& event) {
        m_States[m_ActiveState]->OnEvent(event);
    };
    void OnUpdate(float dt) {
        CVData().m_WorldMousePos = ScreenToWorld(CVData().m_WindowMousePos);

        static glm::vec2 lastPos = { 0, 0 };
        CVData().m_WorldMouseDelta = CVData().m_WorldMousePos - glm::vec2(CVData().m_CameraController->GetCamera().GetPosition()) - lastPos;
        lastPos = CVData().m_WorldMousePos - glm::vec2(CVData().m_CameraController->GetCamera().GetPosition());
        
        m_NextState = m_States[m_ActiveState]->GetNextState();
        if (!m_IsTransitioning && m_ActiveState != m_NextState) {
            m_IsTransitioning = true;
            m_States[m_ActiveState]->OnExit();
            m_ActiveState = m_NextState;
            m_States[m_ActiveState]->OnEnter();
            m_IsTransitioning = false;
        }
        else if (!m_IsTransitioning) {
            m_States[m_ActiveState]->OnUpdate(dt);
        }
    }; 
    void OnRender() { }; 
    void OnCanvasRender() {
        CVData().m_WindowMousePos = ImGui::GetMousePos() - ImGui::GetWindowPos() 
            - ImVec2(0, ImGui::GetWindowHeight() - CVData().m_ViewportSize.y);

        ImGui::GetWindowDrawList()->AddCircleFilled(
            WorldToScreen(CVData().m_WorldMousePos), 
            10 / CVData().m_CameraController->GetZoomLevel(), 
            IM_COL32(255, 255, 0, 255)
        );
    }; 
private:
    std::vector<BaseState*> m_States;
    StateKey m_ActiveState, m_NextState;
    bool m_IsTransitioning;
};
