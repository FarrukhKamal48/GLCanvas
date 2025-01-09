#include "GLCanvas/CanvasLayer.h"
#include "Cards/CardObject.h"
#include "GLCanvas/ImVec2Extend.h"

#define PI glm::pi<float>()

CanvasLayer::CanvasLayer() 
    : Layer("Canvas Layer")
    , m_CameraController(16.0f/9.0f, 1.0f) 
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
}

void CanvasLayer::OnAttach() {
    Renderer::SetCamera(m_CameraController.GetCamera());
    m_BackgroundI = m_Manager.AllocateObject(10, [](InstanceRenderer& renderer) {
        renderer.CreateShader("Assets/Shaders/Card.vert", 
                              "Assets/Shaders/Card.frag");
    });
    
    for (int i = 0; i < 10; i++) {
        m_Manager[m_BackgroundI+i].position = glm::vec3(glm::cos(i), glm::sin(i), -1);
        m_Manager[m_BackgroundI+i].scale = glm::vec2(0.05);
        m_Manager[m_BackgroundI+i].rotation = PI/4;
        m_Manager[m_BackgroundI+i].color = glm::vec4(i/10.0f, glm::sin(i), i/15.0f, 1.0f);
        m_Manager[m_BackgroundI+i].cardID = 1;
    }

    m_Manager[m_BackgroundI].position = {0,0,1};
    m_Manager[m_BackgroundI].scale = glm::vec2(0.05);
    m_Manager[m_BackgroundI].rotation = PI/4;
    m_Manager[m_BackgroundI].color = glm::vec4(0,0,0,1);
    m_Manager[m_BackgroundI].cardID = 1;
}

void CanvasLayer::OnUpdate(float dt) {
    
    if (Input::KeyPressed(Key::LeftAlt) && Input::MousePressed(Mouse::ButtonLeft))
        m_CameraController.Translate(-glm::vec3(m_WorldMouseDelta, 0.0f));
    
    m_WorldMousePos = ScreenToWorld(m_WindowMousePos);

    static glm::vec2 lastPos = { 0, 0 };
    m_WorldMouseDelta = m_WorldMousePos - glm::vec2(m_CameraController.GetCamera().GetPosition()) - lastPos;
    lastPos = m_WorldMousePos - glm::vec2(m_CameraController.GetCamera().GetPosition());
    
    if (Input::KeyPressed(Key::Space))
        m_Manager[m_BackgroundI].scale = Lerp(m_Manager[m_BackgroundI].scale, glm::vec2(0.01f), dt * 10.0f);
    else
        m_Manager[m_BackgroundI].scale = Lerp(m_Manager[m_BackgroundI].scale, glm::vec2(0.05f), dt * 10.0f);
    
    // m_Manager[m_BackgroundI].position = glm::vec3(m_WorldMousePos, 0.0f);
    m_Manager[m_BackgroundI].rotation += 5 * dt;
}

void CanvasLayer::OnRender() {
    m_Framebuffer.Bind();
    Renderer::Clear(0.9, 0.9, 0.9, 1);
    m_Framebuffer.ClearAttachment(1, -1);
}

void CanvasLayer::OnImGuiRender() {
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
    ImGui::Begin("Canvas");
    {
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if (m_ViewportSize != viewportSize) {
            m_ViewportSize = { viewportSize.x, viewportSize.y };
            m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
            m_Framebuffer.Resize(viewportSize.x, viewportSize.y);
        }
        ImGui::Image(m_Framebuffer.GetColorAttachment(), viewportSize, ImVec2(0,1), ImVec2(1,0));

        m_WindowMousePos = ImGui::GetMousePos() - ImGui::GetWindowPos() 
            - ImVec2(0, ImGui::GetWindowHeight() - m_ViewportSize.y);

        ImGui::GetWindowDrawList()->AddCircleFilled(
            WorldToScreen(m_WorldMousePos), 
            10 / m_CameraController.GetZoomLevel(), 
            IM_COL32(255, 255, 0, 255)
        );

        auto [mx, my] = m_WindowMousePos;
        my = viewportSize.y - my;

        int pixeldata = m_Framebuffer.ReadPixel(1, mx, my);
        BASIC_LOG(pixeldata);
        
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

glm::vec2 CanvasLayer::ScreenToWorld(ImVec2 screenCoords) {
    return glm::vec2(
        screenCoords.x/m_ViewportSize.x - 0.5f,
        1.0f - screenCoords.y/m_ViewportSize.y - 0.5f
    ) * m_CameraController.GetBounds() + glm::vec2(m_CameraController.GetCamera().GetPosition());
}

ImVec2 CanvasLayer::WorldToScreen(glm::vec2 worldCoords) {
    return glm::vec2(
        0.5f + (worldCoords.x - m_CameraController.GetCamera().GetPosition().x)/m_CameraController.GetBounds().x,
        0.5f - (worldCoords.y - m_CameraController.GetCamera().GetPosition().y)/m_CameraController.GetBounds().y
    ) * m_ViewportSize + ImGui::GetWindowPos() + glm::vec2(0, ImGui::GetWindowHeight() - m_ViewportSize.y);
}

