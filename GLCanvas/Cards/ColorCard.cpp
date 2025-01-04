#include "GLCanvas/Cards/ColorCard.h"

ColorCard::ColorCard(const ColorCardSpec& spec) : m_Spec(spec) {
    m_ColorRectI = m_Manager.AllocateObject(2, BIND_FN(ConfigureShader));
    m_TitleRectI = m_ColorRectI + 1;
    UpdateData();   
}

void ColorCard::OnEvent(Event& event) {
    EventDispacher dispacher(event);
    dispacher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& event) {
        m_IsDragged = Input::MousePressed(Mouse::ButtonLeft) && 
            IsHovered(m_Spec.Position - m_Spec.Scale, m_Spec.Position + m_Spec.Scale, m_WorldMousePos);
        return false;
    });
}

void ColorCard::OnUpdate(float dt) {
    if (m_IsDragged) {
        m_Spec.Position += m_WorldMouseDelta;
        m_Manager[m_ColorRectI].position = glm::vec3(m_Spec.Position, 0);
        m_Manager[m_TitleRectI].position = 
            glm::vec3(m_Spec.Position.x, m_Spec.Position.y - m_Spec.Scale.y * m_Spec.TitlePercent, 0);
    }
}

void ColorCard::UpdateData() {
    m_Manager[m_ColorRectI].color = m_Spec.Color;
    m_Manager[m_ColorRectI].scale = m_Spec.Scale;
    m_Manager[m_ColorRectI].position = glm::vec3(m_Spec.Position, 0);
    m_Manager[m_ColorRectI].rotation = 0;
    
    m_Manager[m_TitleRectI].color = { 0.1f, 0.1f, 0.1f, 1.0f };
    m_Manager[m_TitleRectI].scale = glm::vec2(m_Spec.Scale.x, m_Spec.Scale.y * m_Spec.TitlePercent);
    m_Manager[m_TitleRectI].position = 
        glm::vec3(m_Spec.Position.x, m_Spec.Position.y - m_Spec.Scale.y * m_Spec.TitlePercent, 0);
    m_Manager[m_TitleRectI].rotation = 0;
}

void ColorCard::ConfigureShader(InstanceRenderer& renderer) {
    renderer.CreateShader("Assets/Shaders/ColorQuad.vert", 
                          "Assets/Shaders/ColorQuad.frag");
}
