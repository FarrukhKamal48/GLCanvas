#pragma once

#include "GLBox/Core/Input.h"
#include <GLBox.h>

#define PI glm::pi<float>()
#define TwoPI 2 * glm::pi<float>()
#define MAXSPEED (float)5

class DynamicLayer : public Layer {
private:
    QuadTransform_Manager m_Manager;
public:
    DynamicLayer() 
        : Layer("Dynamic Test")
    { }
    ~DynamicLayer() { }

    void OnAttach() override {
    }

    void OnDetach() override {
        
    }

    void Update(float dt) override {
    }

    void Render() override {
    }

    void ImGuiRender() override {
        ImGui::ShowDemoWindow();
        ImGui::Begin("Sim Controls");
        static int inc = 0;
        if (ImGui::Button("Spawn Square", ImVec2(100, 100))) {
            unsigned int objI = m_Manager.AllocateObject(1, &ConfigureShader);
            inc++;
            m_Manager[objI].position = 
                glm::vec2(inc * 0.01f * glm::sin(inc) + 0.005f, inc*0.01f);
            m_Manager[objI].scale = glm::vec2(0.01f);
            m_Manager[objI].rotation = inc*glm::sin(inc*20);
            m_Manager[objI].color = glm::vec4(1, 0.5, 0, 1);
        }
        ImGui::End();
    }
private:
    static void ConfigureShader(InstanceRenderer& renderer) {
        renderer.CreateShader("GLBox/assets/shaders/instancing/RotationQuad.vert", 
                              "GLBox/assets/shaders/instancing/RotationQuad.frag");
    }

    glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float p) {
        return a + p * (b-a);
    }
};


class SpinLayer : public Layer {
private:
    QuadTransform_Manager m_Manager;
    unsigned int m_Test;
    glm::vec2 m_MousePos = { 0, 0 };
    glm::vec2 m_WindowSize = { 1920, 1080 };
    OrthoCameraController m_CameraController;
public:
    SpinLayer() 
        : Layer("Spin Test")
        , m_CameraController(16.0f/9.0f, 1.0f)
    { }
    ~SpinLayer() { }

    void OnEvent(Event& event) override {
        EventDispacher dispacher(event);       
        dispacher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& event){
            m_MousePos = { 
                (event.GetX()/m_WindowSize.x * 2.0f - 1.0f) * m_CameraController.GetBounds().x * 0.5f, 
                ((1.0f - event.GetY()/m_WindowSize.y) * 2.0f - 1.0f) * m_CameraController.GetBounds().y * 0.5f 
            };
            return false;
        });
        dispacher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& event) {
            m_WindowSize = { event.GetWidth(), event.GetHeight() };
            return false;
        });
        m_CameraController.OnEvent(event);
    }

    void OnAttach() override {
        Renderer::SetCamera(m_CameraController.GetCamera());
        m_Test = m_Manager.AllocateObject(1, &ConfigureShader);

        m_Manager[m_Test].position = {0,0};
        m_Manager[m_Test].scale = glm::vec2(0.05);
        m_Manager[m_Test].rotation = PI/4;
        m_Manager[m_Test].color = glm::vec4(0,0,0,0.6);
    }

    void OnDetach() override {
        
    }

    bool spawn = true;
    void Update(float dt) override {
        m_Manager[m_Test].position = m_MousePos;
        m_Manager[m_Test].rotation += dt * 5;

        if (Input::MousePressed(Mouse::ButtonLeft))
            m_Manager[m_Test].scale = Lerp(m_Manager[m_Test].scale, glm::vec2(0.01f), dt * 10.0f);
        else
            m_Manager[m_Test].scale = Lerp(m_Manager[m_Test].scale, glm::vec2(0.05f), dt * 10.0f);
    }

    void Render() override {
    }

    void ImGuiRender() override {
    }
private:
    static void ConfigureShader(InstanceRenderer& renderer) {
        renderer.CreateShader("GLBox/assets/shaders/instancing/RotationQuad.vert", 
                              "GLBox/assets/shaders/instancing/RotationQuad.frag");
    }

    glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float p) {
        return a + p * (b-a);
    }
};
