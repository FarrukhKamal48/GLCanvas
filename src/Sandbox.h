#pragma once
#include <iostream>
#include <GLBox.h>
#include "Core/Layer.h"


class OtherLayer : public Layer {
private:
    Pos_Scale_Col_Quad_Manager m_Manager;
    unsigned int m_O;
public:
    OtherLayer() : Layer("Verlet Test") { }
    ~OtherLayer() { }

    void OnAttach() override {
        m_O = m_Manager.AllocateObject(10, &ConfigureShader);
        m_Manager[m_O].scale = glm::vec2(100);
        m_Manager[m_O].scale = glm::vec4(1,1,1,1);
        m_Manager[m_O].position = glm::vec2(100, 100);
        std::cout << "Attached" << '\n';
    }

    void OnDetach() override {
        std::cout << "Detached" << '\n';
    }
    void Update(float dt) override {
        // m_O.position.x += dt;
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
