#pragma once
#include <iostream>
#include <GLBox.h>
#include "Core/Layer.h"


class OtherLayer : public Layer {
private:
    Pos_Scale_Col_Quad_Manager m_Manager;
public:
    OtherLayer() 
        : Layer("Verlet Test")
    {
        // m_Manager.Instantiate(1, &ConfigureShader);
    }
    ~OtherLayer() { }

    void OnAttach() override {
        // m_O.scale = glm::vec2(100);
        // m_O.scale = glm::vec4(1,1,1,1);
        // m_O.position = glm::vec2(WIDTH/2, HEIGHT/2);
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
