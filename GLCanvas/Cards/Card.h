#pragma once
#include <glbpch.h>
#include <GLBox.h>
#include "ImVec2Extend.h"

struct CanvasData {
    const glm::vec2& CameraBounds;
    glm::vec2 ViewportSize = { 0, 0 };
    glm::vec2 WorldMouseDelta = { 0, 0 };
    glm::vec2 WorldMousePos = { 0, 0 };
    ImVec2 WindowMousePos = { 0, 0 };
    CanvasData(const glm::vec2& bounds) : CameraBounds(bounds) {}
};

class Card {
public:
    Card(CanvasData& data) : m_CanvasData(data) {};
    virtual ~Card() {};

    static bool IsHovered(glm::vec2 bottomleft, glm::vec2 topright, glm::vec2 mouse) { 
        return mouse.x >= bottomleft.x && mouse.x <= topright.x && 
               mouse.y >= bottomleft.y && mouse.y <= topright.y;
    }
    static ImVec2 WorldToScreen(glm::vec2 worldCoords, CanvasData& canvasData) {
        return glm::vec2(
            0.5f + worldCoords.x/canvasData.CameraBounds.x,
            0.5f - worldCoords.y/canvasData.CameraBounds.y
        ) * canvasData.ViewportSize + ImGui::GetWindowPos() + glm::vec2(0, ImGui::GetWindowHeight() - canvasData.ViewportSize.y);
    }

    virtual void OnEvent(Event& event) {};
    
    virtual void OnUpdate(float dt) {};
    virtual void OnRender() {};
    virtual void OnImGuiRender() {};
protected:
    CanvasData& m_CanvasData;
};
