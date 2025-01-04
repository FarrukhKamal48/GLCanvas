#pragma once
#include "GLCanvas/Cards/Card.h"

struct ColorCardSpec {
    glm::vec2 Position = { 0, 0 };
    glm::vec4 Color = { 1,1,1,1 };
    glm::vec2 Scale = { 0.2f, 0.2f };
    float TitlePercent = 0.5f;
};

class ColorCard : public Card {
public:    
    ColorCard(const ColorCardSpec& spec);
    ~ColorCard() {}

    void OnEvent(Event& event) override;
    void OnUpdate(float dt) override;
    
    void SetSpec(const ColorCardSpec& spec) { m_Spec = spec; UpdateData(); }
    ColorCardSpec& GetSpec() { return m_Spec; }
private:
    void UpdateData();
    
    void ConfigureShader(InstanceRenderer& renderer);
private:
    QuadTransform_Manager m_Manager;
    uint32_t m_ColorRectI = -1;
    uint32_t m_TitleRectI = -1;
    
    ColorCardSpec m_Spec;
    bool m_IsDragged = false;
    glm::vec2 m_WindowMousePos;
};
