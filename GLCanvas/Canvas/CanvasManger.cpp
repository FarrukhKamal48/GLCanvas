#include "GLCanvas/ImVec2Defines.h"
#include "GLCanvas/Canvas/CanvasManager.h"

namespace Canvas {

CanvasManager::CanvasManager() {
    CVData().Cardmanager = &m_CardManger;
    
    m_States.reserve(StateType::COUNT);
    for (StateKey type = StateType::Idle; type < StateType::COUNT; type++) {
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
    
    static StateKey m_NextState;
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
