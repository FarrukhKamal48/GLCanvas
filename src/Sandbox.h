#pragma once
#include "Core/Input.h"
#include "Core/Layer.h"
#include "Core/Application.h"
#include "Core/Instancing/RendererInstanced.h"
#include "glm/fwd.hpp"
#include "imgui.h"

#define PI glm::pi<float>()
#define TwoPI 2 * glm::pi<float>()
#define MAXSPEED (float)5

class OtherLayer : public Layer {
private:
    Pos_Scale_Col_Quad_Manager m_Manager;
    unsigned int m_Test;
public:
    OtherLayer() 
        : Layer("Other Test")
    { }
    ~OtherLayer() { }

    void OnAttach() override {
        m_Test = m_Manager.AllocateObject(1, &ConfigureShader);            

        // set graphic for contraint
        m_Manager[m_Test].position = glm::vec2(WIDTH, HEIGHT)/2.0f;
        m_Manager[m_Test].scale = glm::vec2(100);
        m_Manager[m_Test].color = glm::vec4(0,0,0,1);
    }

    void OnDetach() override {
        
    }

    void Update(float dt) override {
        // m_ObjData[0].position = Lerp(m_ObjData[1].position, 
        //                              glm::vec2(Input::GetMousePos().x, HEIGHT - Input::GetMousePos().y), 10 * dt);
        m_Manager[m_Test].position = glm::vec2(Input::GetMousePos().x, HEIGHT - Input::GetMousePos().y);

        if (Input::Button(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS))
            m_Manager[m_Test].scale = Lerp(m_Manager[m_Test].scale, glm::vec2(8.0f), dt * 10.0f);
        else
            m_Manager[m_Test].scale = Lerp(m_Manager[m_Test].scale, glm::vec2(100.0f), dt * 10.0f);
    }

    void Render() override {
    }

    void ImGuiRender() override {
        ImGui::ShowDemoWindow();
    }
private:
    static void ConfigureShader(InstanceRenderer& renderer) {
        renderer.CreateShader("vendor/GLBox/assets/shaders/instancing/BasicColorScale.vert", 
                            "vendor/GLBox/assets/shaders/instancing/CircleInRectColor.frag");
        renderer.InstanceShader->SetUniform<float>("u_CullRadius", 0.5f);
        renderer.InstanceShader->SetUniform<float>("u_EdgeSmooth", 1.2f);
    }

    glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float p) {
        return a + p * (b-a);
    }
};


