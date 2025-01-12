#include "GLCanvas/CanvasLayer.h"
#include "Cards/CardObject.h"
#include "GLCanvas/ImVec2Extend.h"

#define PI glm::pi<float>()

CanvasLayer::CanvasLayer() 
    : Layer("Canvas Layer")
    , m_CameraController(16.0f/9.0f, 1.0f) 
    , m_CanvasManager(CanvasState::Idle, m_CameraController)
{
    FBSpec spec;
    spec.Width = 1920;
    spec.Height = 1080;
    spec.Attachments = { FBTextureFormat::RGBA8, FBTextureFormat::RED_INTEGER, FBTextureFormat::DEPTH24STENCIL8 };
    m_Framebuffer = FrameBuffer(spec);
}
CanvasLayer::~CanvasLayer() { }

void CanvasLayer::OnEvent(Event& event) {
    EventDispacher dispacher(event);
    m_CameraController.OnEvent(event);
    m_CanvasManager.OnEvent(event);
}

void CanvasLayer::OnAttach() {
    Renderer::SetCamera(m_CameraController.GetCamera());
    m_BackgroundI = m_Manager.AllocateObject(10, [](InstanceRenderer& renderer) {
        renderer.CreateShader("Assets/Shaders/Card.vert", 
                              "Assets/Shaders/Card.frag");
    });
    
    for (int i = 0; i < 10; i++) {
        m_Manager[m_BackgroundI+i].position = glm::vec3(glm::cos(i), glm::sin(i), 0);
        m_Manager[m_BackgroundI+i].scale = glm::vec2(0.05);
        m_Manager[m_BackgroundI+i].rotation = PI/4;
        m_Manager[m_BackgroundI+i].color = glm::vec4(i/10.0f, glm::sin(i), i/15.0f, 1.0f);
        m_Manager[m_BackgroundI+i].cardID = i;
    }
    m_Manager[m_BackgroundI+9].position = glm::vec3(0.0f, 0.05f, 0.9f);

    m_Manager[m_BackgroundI].position = {0,0,0};
    m_Manager[m_BackgroundI].scale = glm::vec2(0.05);
    m_Manager[m_BackgroundI].rotation = PI/4;
    m_Manager[m_BackgroundI].color = glm::vec4(0,0,0,1);
    m_Manager[m_BackgroundI].cardID = 0;
}

void CanvasLayer::OnUpdate(float dt) {
    m_Framebuffer.Bind();
    
    auto [mx, my] = m_CanvasManager.Data().m_WindowMousePos;
    my = m_CanvasManager.Data().m_ViewportSize.y - my;
    m_HoveredCardID = m_Framebuffer.ReadPixel(1, mx, my);

    m_CanvasManager.OnUpdate(dt);

    // m_InputState = NextInputSate();
    // switch (m_InputState) {
    //     case InputState::Idle: 
    //         m_Manager[m_BackgroundI].rotation += 5 * dt;
    //         break;
    //     case InputState::Panning: 
    //         m_CameraController.Translate(-glm::vec3(m_WorldMouseDelta, 0.0f));
    //         break;
    //     case InputState::DraggCard:
    //         m_Manager[m_HoveredCardID].position += glm::vec3(m_WorldMouseDelta, 0.0f);
    //         m_Manager[m_HoveredCardID].position.z = 1.0f;
    //         break;
    //     case InputState::DraggSelect:
    //         // BASIC_LOG("Not Implimented");
    //         break;
    // }
}

void CanvasLayer::OnRender() {
    Renderer::Clear(0.9,0.9,0.9,1);
    m_Framebuffer.ClearAttachment(1, -1);
    m_CanvasManager.OnRender();
}

void CanvasLayer::OnImGuiRender() {
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
    ImGui::Begin("Canvas");
    {
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if (m_CanvasManager.Data().m_ViewportSize != viewportSize) {
            m_CanvasManager.Data().m_ViewportSize = { viewportSize.x, viewportSize.y };
            m_CameraController.OnResize(viewportSize.x, viewportSize.y);
            m_Framebuffer.Resize(viewportSize.x, viewportSize.y);
        }
        ImGui::Image(m_Framebuffer.GetColorAttachment(), viewportSize, ImVec2(0,1), ImVec2(1,0));
        m_CanvasManager.OnCanvasRender();
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

glm::vec2 CanvasLayer::Lerp(glm::vec2 a, glm::vec2 b, float p) {
    return a + p * (b-a);
}

