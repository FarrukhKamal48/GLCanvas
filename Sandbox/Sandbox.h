#pragma once

#include <GLBox/Core/Application.h>
#include <GLBox/Renderer/RendererInstanced.h>

#include "GLBox/Events/KeyEvent.h"
#include "GLBox/Events/MouseEvent.h"

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
            m_Manager[objI].position = glm::vec2(inc * 50 * glm::sin(inc) + (float)WIDTH/2,
                                                 inc*5);
            m_Manager[objI].scale = glm::vec2(20);
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
    glm::vec2 m_MousePos;
    bool m_MouseDown = false;
public:
    SpinLayer() 
        : Layer("Spin Test")
    { }
    ~SpinLayer() { }

    void OnEvent(Event& event) override {
        EventDispacher dispacher(event);       
        dispacher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& event){
            m_MousePos = { event.GetX(), event.GetY() };
            return false;
        });
        dispacher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event){
            if (event.GetKeyCode() == GLFW_KEY_F)
                m_MouseDown = true;
            return false;
        });
        dispacher.Dispatch<KeyReleasedEvent>([this](KeyReleasedEvent& event){
            if (event.GetKeyCode() == GLFW_KEY_F)
                m_MouseDown = false;
            return false;
        });
    }

    void OnAttach() override {
        m_Test = m_Manager.AllocateObject(1, &ConfigureShader);

        m_Manager[m_Test].position = glm::vec2(WIDTH, HEIGHT)/2.0f;
        m_Manager[m_Test].scale = glm::vec2(50);
        m_Manager[m_Test].rotation = PI/4;
        m_Manager[m_Test].color = glm::vec4(0,0,0,0.6);
    }

    void OnDetach() override {
        
    }

    bool spawn = true;
    void Update(float dt) override {
        m_Manager[m_Test].position = glm::vec2(m_MousePos.x, HEIGHT - m_MousePos.y);
        m_Manager[m_Test].rotation += dt * 5;

        if (m_MouseDown)
            m_Manager[m_Test].scale = Lerp(m_Manager[m_Test].scale, glm::vec2(8.0f), dt * 10.0f);
        else
            m_Manager[m_Test].scale = Lerp(m_Manager[m_Test].scale, glm::vec2(50.0f), dt * 10.0f);
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
