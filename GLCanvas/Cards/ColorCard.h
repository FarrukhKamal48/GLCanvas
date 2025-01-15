#pragma once
#include <glbpch.h>
#include "GLCanvas/Cards/CardObject.h"
#include "GLCanvas/Cards/Card.h"

class ColorCard : public Card {
public: 
    ColorCard(uint32_t cardID, glm::vec3 pos) : Card(CardType::ColorCard), m_CardID(cardID) {
        m_ObjI = m_Allocator.AllocateObject(1, [](InstanceRenderer& renderer) {
            renderer.CreateShader("Assets/Shaders/Card.vert", 
                                  "Assets/Shaders/Card.frag");
        });
        m_Allocator[m_ObjI].position = pos;
        m_Allocator[m_ObjI].scale = glm::vec2(0.1);
        m_Allocator[m_ObjI].rotation = 0;
        m_Allocator[m_ObjI].color = glm::vec4(0,0,0,1);
        m_Allocator[m_ObjI].cardID = m_CardID;
    }
    ~ColorCard() {}

    void OnEvent(Event& event) override { }
    void OnUpdate(float dt) override { } 
    void OnImGuiRender() override { } 
    
    void Drag(glm::vec3 delta) override { 
        m_Allocator[m_ObjI].position += delta;
    }
    void SetZDepth(float zdepth) override {
        m_Allocator[m_ObjI].position.z = zdepth;
    }
private:
    uint32_t m_CardID;
    CardTransform_Manager m_Allocator;
    uint32_t m_ObjI;
};
