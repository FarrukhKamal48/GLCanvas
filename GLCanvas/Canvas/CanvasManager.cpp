#include "GLCanvas/Base.h"
#include "GLCanvas/Canvas/CanvasManager.h"

namespace Canvas {

CanvasManager::CanvasManager() {
    CVData().Cardmanager = &m_CardManger;
    
    m_States.reserve(StateType::COUNT);
    for (StateKey type = StateType::Main; type < StateType::COUNT; type++) {
        m_States[type] = State::Create(type);
    }

    m_CardManger.AddCard(CardType::ColorCard, glm::vec3(0));
    m_CardManger.AddCard(CardType::ColorCard, glm::vec3(1));
    
    m_States[m_ActiveState]->OnEnter();
}

CanvasManager::~CanvasManager() {
    for (State* state : m_States) {
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
    
    static StateKey nextState;
    nextState = m_States[m_ActiveState]->GetNextState();
    static bool transitionInLock; 
    transitionInLock = (m_ActiveState != StateType::Main && nextState == StateType::Main);
    if ((!m_IsLocked && m_ActiveState != nextState) || transitionInLock) {
        TransitionTo(nextState);
    }
    else {
        m_States[m_ActiveState]->OnUpdate(dt);
    }
    m_CardManger.OnUpdate(dt);
}; 

void CanvasManager::OnRender() { }; 

void CanvasManager::OnImGuiRender() {
    CVData().WindowMousePos = ImGui::GetMousePos() - ImGui::GetWindowPos() 
        - ImVec2(0, ImGui::GetWindowHeight() - CVData().ViewportSize.y);
    CVData().ImGuiMousePos = ImGui::GetMousePos();
    
    ImGui::GetWindowDrawList()->AddCircleFilled(
        WorldToScreen(CVData().WorldMousePos), 
        10 / CVData().Camera->GetZoomLevel(), 
        IM_COL32(255, 255, 0, 255)
    );
    
    m_States[m_ActiveState]->OnImGuiRender();
    m_CardManger.OnImGuiRender();
}; 

void CanvasManager::TransitionTo(StateKey nextState) {
    m_IsTransitioning = true;
    m_States[m_ActiveState]->OnExit();
    m_ActiveState = nextState;
    m_States[m_ActiveState]->OnEnter();
    m_IsTransitioning = false;
}

}
