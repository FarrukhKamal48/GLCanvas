#pragma once
#include <GLBox.h>
#include "GLCanvas/Canvas/CanvasStates.h"
#include "GLCanvas/ImVec2Extend.h"

class CanvasManager {
public:
    CanvasManager(FSMKey startState, OrthoCameraController& camera) 
        : m_ActiveState(startState), m_NextState(startState) 
        , m_Data({camera})
    {
        m_States.reserve(CanvasState::MAX);
        m_States[CanvasState::Idle] = new IdleState(CanvasState::Idle, m_Data);
        m_States[CanvasState::Panning] = new PanningState(CanvasState::Panning, m_Data);
        m_States[m_ActiveState]->OnEnter();
    }
    ~CanvasManager() {
        for (State* state : m_States) {
            delete state;
        }
    }
    
    void OnEvent(Event& event) {
        m_States[m_ActiveState]->OnEvent(event);
    };
    void OnUpdate(float dt) {
        m_Data.m_WorldMousePos = ScreenToWorld(m_Data.m_WindowMousePos);

        static glm::vec2 lastPos = { 0, 0 };
        m_Data.m_WorldMouseDelta = m_Data.m_WorldMousePos - glm::vec2(m_Data.m_CameraController.GetCamera().GetPosition()) - lastPos;
        lastPos = m_Data.m_WorldMousePos - glm::vec2(m_Data.m_CameraController.GetCamera().GetPosition());
        
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
        m_Data.m_WindowMousePos = ImGui::GetMousePos() - ImGui::GetWindowPos() 
            - ImVec2(0, ImGui::GetWindowHeight() - m_Data.m_ViewportSize.y);

        ImGui::GetWindowDrawList()->AddCircleFilled(
            WorldToScreen(m_Data.m_WorldMousePos), 
            10 / m_Data.m_CameraController.GetZoomLevel(), 
            IM_COL32(255, 255, 0, 255)
        );
    }; 

    FSMData& Data() { return m_Data; }
private:
    glm::vec2 ScreenToWorld(ImVec2 screenCoords) {
        return glm::vec2(
            screenCoords.x/m_Data.m_ViewportSize.x - 0.5f,
            1.0f - screenCoords.y/m_Data.m_ViewportSize.y - 0.5f
        ) * m_Data.m_CameraController.GetBounds() + glm::vec2(m_Data.m_CameraController.GetCamera().GetPosition());
    }
    ImVec2 WorldToScreen(glm::vec2 worldCoords) {
        return glm::vec2(
            0.5f + (worldCoords.x - m_Data.m_CameraController.GetCamera().GetPosition().x)/m_Data.m_CameraController.GetBounds().x,
            0.5f - (worldCoords.y - m_Data.m_CameraController.GetCamera().GetPosition().y)/m_Data.m_CameraController.GetBounds().y
        ) * m_Data.m_ViewportSize + ImGui::GetWindowPos() + glm::vec2(0, ImGui::GetWindowHeight() - m_Data.m_ViewportSize.y);
    }
private:
    std::vector<State*> m_States;
    FSMKey m_ActiveState, m_NextState;
    FSMData m_Data;
    bool m_IsTransitioning;
};
