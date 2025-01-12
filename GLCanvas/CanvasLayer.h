#pragma once
#include <glbpch.h>
#include <GLBox.h>

#include "Cards/CardObject.h"
#include "GLCanvas/Canvas/CanvasManager.h"

class CanvasLayer : public Layer {
private:
    OrthoCameraController m_CameraController;
    FrameBuffer m_Framebuffer;
    
    CardTransform_Manager m_Manager;
    uint32_t m_BackgroundI = -1;
    
    Canvas::CanvasManager m_CanvasManager;
public:
    CanvasLayer();
    ~CanvasLayer();

    void OnEvent(Event& event) override;
    void OnAttach() override;
    void OnUpdate(float dt) override; 
    void OnRender() override; 
    void OnImGuiRender() override; 
private:
    glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float p);
};
