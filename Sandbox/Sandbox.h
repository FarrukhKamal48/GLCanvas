#pragma once

#include <glbpch.h>
#include <GLBox.h>

#define PI glm::pi<float>()
#define TwoPI 2 * glm::pi<float>()
#define MAXSPEED (float)5

class SpinLayer : public Layer {
private:
    QuadTransform_Manager m_Manager;
    uint32_t m_Test;
    
    OrthoCameraController m_CameraController;
    FrameBuffer m_Framebuffer;
    glm::vec2 m_ViewportSize = { 0, 0 };

    glm::vec2 m_WishDir = { 0, 0 };
    glm::vec2 m_MouseDelta = { 0, 0 };
    glm::vec2 m_MousePos = { 0, 0 };
public:
    SpinLayer() 
        : Layer("Spin Test")
        , m_CameraController(16.0f/9.0f, 1.0f)
        , m_Framebuffer({ 1920, 1080, false })
    { }
    ~SpinLayer() { }

    void OnEvent(Event& event) override {
        EventDispacher dispacher(event);
        m_CameraController.OnEvent(event);
    }

    void OnAttach() override {
        Renderer::SetCamera(m_CameraController.GetCamera());
        
        m_Test = m_Manager.AllocateObject(2, BIND_FN(ConfigureShader));

        m_Manager[m_Test].position = {0,0};
        m_Manager[m_Test].scale = glm::vec2(0.05);
        m_Manager[m_Test].rotation = PI/4;
        m_Manager[m_Test].color = glm::vec4(0,0,0,0.6);
        
    }

    void OnUpdate(float dt) override {
        if (Input::KeyPressed(Key::Space))
            m_Manager[m_Test].scale = Lerp(m_Manager[m_Test].scale, glm::vec2(0.01f), dt * 10.0f);
        else
            m_Manager[m_Test].scale = Lerp(m_Manager[m_Test].scale, glm::vec2(0.05f), dt * 10.0f);
        
        // if (Input::KeyPressed(Key::W))          m_WishDir.y = 1;
        // else if (Input::KeyPressed(Key::S))     m_WishDir.y = -1;
        // else                                    m_WishDir.y = 0;
        // 
        // if (Input::KeyPressed(Key::D))          m_WishDir.x = 1;
        // else if (Input::KeyPressed(Key::A))     m_WishDir.x = -1;
        // else                                    m_WishDir.x = 0;
        //
        // m_CameraController.Translate(glm::vec3(m_WishDir.x, m_WishDir.y, 0.0f) * 2.0f * dt);
        
        // m_Manager[m_Test].position += m_WishDir * 2.0f * dt;
        m_Manager[m_Test].position = m_MousePos;
        m_Manager[m_Test].rotation += 5 * dt;

        // static glm::vec2 lastPos = { 0, 0 };
        // m_MouseDelta = m_MousePos - lastPos;
        // lastPos = m_MousePos;

    }

    void OnRender() override {
        m_Framebuffer.Bind();
    }

    void OnImGuiRender() override {
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
        ImGui::Begin("ViewPort"); {
            ImVec2 viewportSize = ImGui::GetContentRegionAvail();
            if (m_ViewportSize != *((glm::vec2*)&viewportSize)) {
                m_ViewportSize = { viewportSize.x, viewportSize.y };
                m_Framebuffer.Resize(m_ViewportSize.x, m_ViewportSize.y);
                m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
            }
            ImGui::Image(m_Framebuffer.GetColorAttachment(), viewportSize, ImVec2(0,1), ImVec2(1,0));
                
            {
                ImVec2 mousePos = { 
                    ImGui::GetMousePos().x - ImGui::GetWindowPos().x, 
                    ImGui::GetMousePos().y - ImGui::GetWindowPos().y 
                };
                m_MousePos = {
                    (mousePos.x/m_ViewportSize.x - 0.5f) * m_CameraController.GetBounds().x,
                    (1.0f - mousePos.y/m_ViewportSize.y - 0.5f) * m_CameraController.GetBounds().y,
                };
            }
        }
        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Settings"); {
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
