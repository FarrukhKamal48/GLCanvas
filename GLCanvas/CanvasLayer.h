#pragma once
#include <glbpch.h>
#include <GLBox.h>

#include "GLCanvas/Canvas/CanvasManager.h"

class CanvasLayer : public Layer {
private:
    CanvasCameraController m_CameraController;
    FrameBuffer m_Framebuffer;
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
    bool m_CanvasActive = true;
};
