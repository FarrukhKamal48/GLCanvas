#include "GLCanvas/ImVec2Defines.h"
#include "GLCanvas/Canvas/CanvasManager.h"
#include "GLCanvas/States/IdleState.h"
#include "GLCanvas/States/PanningState.h"

namespace Canvas {

CanvasManager::CanvasManager() {
    m_States.reserve(State::MAX);
    m_States[State::Idle] = new IdleState(State::Idle);
    m_States[State::Panning] = new PanningState(State::Panning);
    m_States[m_ActiveState]->OnEnter();
}

CanvasManager::~CanvasManager() {
    for (BaseState* state : m_States) {
        delete state;
    }
}

void CanvasManager::OnEvent(Event& event) {
    m_States[m_ActiveState]->OnEvent(event);
};

void CanvasManager::OnUpdate(float dt) {
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

void CanvasManager::OnRender() { }; 

void CanvasManager::OnCanvasRender() {
    CVData().m_WindowMousePos = ImGui::GetMousePos() - ImGui::GetWindowPos() 
        - ImVec2(0, ImGui::GetWindowHeight() - CVData().m_ViewportSize.y);

    ImGui::GetWindowDrawList()->AddCircleFilled(
        WorldToScreen(CVData().m_WorldMousePos), 
        10 / CVData().m_CameraController->GetZoomLevel(), 
        IM_COL32(255, 255, 0, 255)
    );
}; 

}
