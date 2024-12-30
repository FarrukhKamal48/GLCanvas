#pragma once
#include "glm/trigonometric.hpp"
#include <Core/Input.h>
#include <Core/Application.h>
#include <Core/Instancing/RendererInstanced.h>

#define PI glm::pi<float>()
#define TwoPI 2 * glm::pi<float>()
#define MAXSPEED (float)5

class DynamicLayer : public Layer {
private:
    QuadTransform_Manager m_Manager;
    unsigned int m_Test;
public:
    DynamicLayer() 
        : Layer("Other Test")
    { }
    ~DynamicLayer() { }

    void OnAttach() override {
        m_Test = m_Manager.AllocateObject(1, &ConfigureShader);

        m_Manager[m_Test].position = glm::vec2(WIDTH, HEIGHT)/2.0f;
        m_Manager[m_Test].scale = glm::vec2(100);
        m_Manager[m_Test].rotation = PI/4;
        m_Manager[m_Test].color = glm::vec4(0,0,0,1);
    }

    void OnDetach() override {
        
    }

    bool spawn = true;
    void Update(float dt) override {
        m_Manager[m_Test].position = glm::vec2(Input::GetMousePos().x, HEIGHT - Input::GetMousePos().y);
        m_Manager[m_Test].rotation += dt * 5;

        if (Input::Button(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS))
            m_Manager[m_Test].scale = Lerp(m_Manager[m_Test].scale, glm::vec2(8.0f), dt * 10.0f);
        else
            m_Manager[m_Test].scale = Lerp(m_Manager[m_Test].scale, glm::vec2(100.0f), dt * 10.0f);
    }

    void Render() override {
    }

    void ImGuiRender() override {
        ImGui::ShowDemoWindow();
        ImGui::Begin("Sim Controls");
        static int inc = 0;
        if (ImGui::Button("Spawn", ImVec2(100, 100))) {
            unsigned int objI = m_Manager.AllocateObject(1, &ConfigureShader);
            inc++;
            m_Manager[objI].position = glm::vec2(inc * 50 * glm::sin(inc) + (float)WIDTH/2,
                                                 inc*5);
            m_Manager[objI].scale = glm::vec2(20);
            m_Manager[objI].rotation = m_Manager[m_Test].rotation;
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


