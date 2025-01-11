#pragma once

#include <glbpch.h>
#include <GLBox.h>
#include "Cards/CardObject.h"

enum class InputState {
    Idle,
    Panning,
    DraggCard,
    DraggSelect,
};

class CanvasLayer : public Layer {
private:
    OrthoCameraController m_CameraController;
    FrameBuffer m_Framebuffer;
    
    CardTransform_Manager m_Manager;
    uint32_t m_BackgroundI = -1;
    
    glm::vec2 m_ViewportSize = { 0, 0 };
    glm::vec2 m_WorldMouseDelta = { 0, 0 };
    glm::vec2 m_WorldMousePos = { 0, 0 };
    ImVec2 m_WindowMousePos = { 0, 0 };

    uint32_t m_HoveredCardID = -1;
    const uint32_t m_InvalidID = -1;
    
    InputState m_InputState = InputState::Idle;
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
    glm::vec2 ScreenToWorld(ImVec2 screenCoords); 
    ImVec2 WorldToScreen(glm::vec2 worldCoords); 

    bool IsValidCard(uint32_t id);
    InputState NextInputSate();
};
