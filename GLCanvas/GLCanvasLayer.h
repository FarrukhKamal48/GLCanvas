#pragma once

#include <glbpch.h>
#include <GLBox.h>

#include "GLCanvas/Canvas/Canvas.h"

class MainLayer : public Layer {
private:
    FrameBuffer m_Framebuffer;
    Canvas m_Canvas;
public:
    MainLayer() 
        : Layer("Spin Test")
        , m_Framebuffer({ 1920, 1080, false })
    { }
    ~MainLayer() { }

    void OnEvent(Event& event) override {
        EventDispacher dispacher(event);
        m_Canvas.OnEvent(event);
    }

    void OnAttach() override {
        Renderer::SetCamera(m_Canvas.GetCameraController().GetCamera());
        m_Canvas.OnAttach();
    }

    void OnUpdate(float dt) override {
        m_Canvas.OnUpdate(dt);
    }

    void OnRender() override {
        m_Framebuffer.Bind();
    }
 
    void OnImGuiRender() override {
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
        ImGui::Begin("Canvas");
        {
            ImVec2 viewportSize = ImGui::GetContentRegionAvail();
            if (m_Canvas.GetViewportSize() != viewportSize) {
                m_Canvas.OnViewportResize({ viewportSize.x, viewportSize.y });
                m_Framebuffer.Resize(viewportSize.x, viewportSize.y);
            }
            ImGui::Image(m_Framebuffer.GetColorAttachment(), viewportSize, ImVec2(0,1), ImVec2(1,0));

            m_Canvas.OnImGuiRender();
        }
        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoTitleBar); 
        {
            ImGui::Button("Hell");
        }
        ImGui::End();
        
        m_Framebuffer.UnBind();
    }
private:
    void ConfigureShader(InstanceRenderer& renderer) {
        renderer.CreateShader("GLBox/assets/shaders/instancing/RotationQuad.vert", 
                              "GLBox/assets/shaders/instancing/RotationQuad.frag");
    }

    glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float p) {
        return a + p * (b-a);
    }
};
