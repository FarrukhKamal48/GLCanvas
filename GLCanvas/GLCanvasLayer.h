#pragma once

#include <glbpch.h>
#include <GLBox.h>

#include "Cards/ColorCard.h"

#define PI glm::pi<float>()

class MyApp;

class MainLayer : public Layer {
private:
    QuadTransform_Manager m_Manager;
    uint32_t m_Test;
    
    OrthoCameraController m_CameraController;
    FrameBuffer m_Framebuffer;
    glm::vec2 m_ViewportSize = { 0, 0 };

    glm::vec2 m_MouseDelta = { 0, 0 };
    glm::vec2 m_WindowMousePos = { 0, 0 };
    glm::vec2 m_WorldMousePos = { 0, 0 };

    ColorCard m_ColorCard;
public:
    MainLayer() 
        : Layer("Spin Test")
        , m_CameraController(16.0f/9.0f, 1.0f)
        , m_Framebuffer({ 1920, 1080, false })
        , m_ColorCard({glm::vec2(0), glm::vec4(1,0,0,1), glm::vec2(0.2f, 0.2f ), 0.5f})
    { }
    ~MainLayer() { }

    void OnEvent(Event& event) override {
        EventDispacher dispacher(event);
        m_CameraController.OnEvent(event);
        m_ColorCard.OnEvent(event);
    }

    void OnAttach() override {
        Renderer::SetCamera(m_CameraController.GetCamera());
        
        m_Test = m_Manager.AllocateObject(10, BIND_FN(ConfigureShader));
        for (int i = 0; i < 10; i++) {
            m_Manager[m_Test+i].position = glm::vec3(glm::cos(i), glm::sin(i), 0.0f);
            m_Manager[m_Test+i].scale = glm::vec2(0.05);
            m_Manager[m_Test+i].rotation = PI/4;
            m_Manager[m_Test+i].color = glm::vec4(i/10.0f, glm::sin(i), i/15.0f, 1.0f);
        }

        m_Manager[m_Test].position = {0,0,0};
        m_Manager[m_Test].scale = glm::vec2(0.05);
        m_Manager[m_Test].rotation = PI/4;
        m_Manager[m_Test].color = glm::vec4(0,0,0,1);
        
    }

    void OnUpdate(float dt) override {
        // take windowMousePos and convert to coords in camera space and then translate my camera's position
        m_WorldMousePos = glm::vec2(
            (m_WindowMousePos.x/m_ViewportSize.x - 0.5f) * m_CameraController.GetBounds().x,
            (1.0f - m_WindowMousePos.y/m_ViewportSize.y - 0.5f) * m_CameraController.GetBounds().y
        ) + glm::vec2(m_CameraController.GetCamera().GetPosition());
        
        static glm::vec2 lastPos = { 0, 0 };
        m_MouseDelta = m_WorldMousePos - lastPos;
        lastPos = m_WorldMousePos;
        
        m_Manager[m_Test].position = glm::vec3(m_WorldMousePos, 0.0f);
        m_Manager[m_Test].rotation += 5 * dt;

        if (Input::KeyPressed(Key::Space))
            m_Manager[m_Test].scale = Lerp(m_Manager[m_Test].scale, glm::vec2(0.01f), dt * 10.0f);
        else
            m_Manager[m_Test].scale = Lerp(m_Manager[m_Test].scale, glm::vec2(0.05f), dt * 10.0f);
        
        if (Input::KeyPressed(Key::LeftAlt) && Input::MousePressed(Mouse::ButtonLeft))
            m_CameraController.Translate(-glm::vec3(m_MouseDelta, 0.0f));

        m_ColorCard.SetMousePos(m_WorldMousePos);
        m_ColorCard.SetMouseDelta(m_MouseDelta);
        m_ColorCard.OnUpdate(dt);
    }

    void OnRender() override {
        m_Framebuffer.Bind();
        m_ColorCard.OnRender();
    }
 
    void OnImGuiRender() override {
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
        ImGui::Begin("ViewPort");
        {
            ImVec2 viewportSize = ImGui::GetContentRegionAvail();
            if (m_ViewportSize != *((glm::vec2*)&viewportSize)) {
                m_ViewportSize = { viewportSize.x, viewportSize.y };
                m_Framebuffer.Resize(m_ViewportSize.x, m_ViewportSize.y);
                m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
            }
            ImGui::Image(m_Framebuffer.GetColorAttachment(), viewportSize, ImVec2(0,1), ImVec2(1,0));
            
            m_WindowMousePos = { 
                ImGui::GetMousePos().x - ImGui::GetWindowPos().x, 
                ImGui::GetMousePos().y - ImGui::GetWindowPos().y - (ImGui::GetWindowHeight() - viewportSize.y) // excluding height of titlebar
            };
            
            m_ColorCard.OnImGuiRender();
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
