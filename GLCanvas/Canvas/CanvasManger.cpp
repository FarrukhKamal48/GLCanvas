#include "GLCanvas/ImVec2Defines.h"
#include "GLCanvas/Canvas/CanvasManager.h"

#include "GLCanvas/States/IdleState.h"
#include "GLCanvas/States/PanningState.h"
#include "GLCanvas/States/DraggCardState.h"

namespace Canvas {

CanvasManager::CanvasManager() {
    CVData().Cardmanager = &m_CardManger;
    m_States.reserve(State::MAX);
    m_States[State::Idle] = new IdleState();
    m_States[State::Panning] = new PanningState();
    m_States[State::DraggCard] = new DraggCardState();
    m_States[m_ActiveState]->OnEnter();

    m_CardManger.AddCard(CardType::ColorCard, glm::vec3(0));
    m_CardManger.AddCard(CardType::ColorCard, glm::vec3(1));
}

CanvasManager::~CanvasManager() {
    for (BaseState* state : m_States) {
        delete state;
    }
}

void CanvasManager::OnEvent(Event& event) {
    m_States[m_ActiveState]->OnEvent(event);
    m_CardManger.OnEvent(event);
};

void CanvasManager::OnUpdate(float dt) {
    CVData().WorldMousePos = ScreenToWorld(CVData().WindowMousePos);

    static glm::vec2 lastPos = { 0, 0 };
    CVData().WorldMouseDelta = CVData().WorldMousePos - glm::vec2(CVData().Camera->GetCamera().GetPosition()) - lastPos;
    lastPos = CVData().WorldMousePos - glm::vec2(CVData().Camera->GetCamera().GetPosition());
    
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
    m_CardManger.OnUpdate(dt);
}; 

void CanvasManager::OnRender() { }; 

void CanvasManager::OnImGuiRender() {
    CVData().WindowMousePos = ImGui::GetMousePos() - ImGui::GetWindowPos() 
        - ImVec2(0, ImGui::GetWindowHeight() - CVData().ViewportSize.y);

    ImGui::GetWindowDrawList()->AddCircleFilled(
        WorldToScreen(CVData().WorldMousePos), 
        10 / CVData().Camera->GetZoomLevel(), 
        IM_COL32(255, 255, 0, 255)
    );

    m_States[m_ActiveState]->OnImGuiRender();
    m_CardManger.OnImGuiRender();
}; 

}
