#include "GLCanvas/ImVec2Defines.h"
#include "GLCanvas/CanvasLayer.h"

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
    Canvas::CVData().Camera = &m_CameraController;
}
CanvasLayer::~CanvasLayer() { }

void CanvasLayer::OnEvent(Event& event) {
    EventDispacher dispacher(event);
    m_CameraController.OnEvent(event);
    m_CanvasManager.OnEvent(event);
}

void CanvasLayer::OnAttach() {
    Renderer::SetCamera(m_CameraController.GetCamera());
}

void CanvasLayer::OnUpdate(float dt) {
    m_Framebuffer.Bind();
    
    auto [mx, my] = Canvas::CVData().WindowMousePos;
    my = Canvas::CVData().ViewportSize.y - my;
    Canvas::CVData().HoveredCardID = m_Framebuffer.ReadPixel(1, mx, my);

    m_CanvasManager.OnUpdate(dt);
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
        if (Canvas::CVData().ViewportSize != viewportSize) {
            Canvas::CVData().ViewportSize = { viewportSize.x, viewportSize.y };
            m_CameraController.OnResize(viewportSize.x, viewportSize.y);
            m_Framebuffer.Resize(viewportSize.x, viewportSize.y);
        }
        ImGui::Image(m_Framebuffer.GetColorAttachment(), viewportSize, ImVec2(0,1), ImVec2(1,0));
        m_CanvasManager.OnImGuiRender();
    }
    ImGui::End();

    ImGui::Begin("Drawer", nullptr, ImGuiWindowFlags_NoTitleBar); 
    {
        ImGui::Button("Press");
    }
    ImGui::End();
    
    ImGui::PopStyleVar();
    m_Framebuffer.UnBind();
}


