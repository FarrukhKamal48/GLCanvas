#include "GLCanvas/ImGuiHelper.h"
#include "GLCanvas/CanvasLayer.h"

#define PI glm::pi<float>()

CanvasLayer::CanvasLayer() 
    : Layer("Canvas Layer")
    , m_CameraController(16.0f/9.0f, 1.0f, false) 
{
    FBSpec spec;
    spec.Width = 1920;
    spec.Height = 1080;
    spec.Attachments = { FBTextureFormat::RGBA8, FBTextureFormat::RED_INTEGER, FBTextureFormat::DEPTH24STENCIL8 };
    m_Framebuffer = FrameBuffer(spec);
    
    Canvas::CVData().Camera = &m_CameraController;
    Application::Get().GetImGuiLayer().SetBlockEvents(false);
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

    m_CameraController.OnUpdate(dt);
    m_CanvasManager.OnUpdate(dt);
}

void CanvasLayer::OnRender() {
    Renderer::Clear(0.9,0.9,0.9,1);
    m_Framebuffer.ClearAttachment(1, -1);
    m_CanvasManager.OnRender();
}

void CanvasLayer::OnImGuiRender() {
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_AutoHideTabBar);
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse;
    
    ImGui::SetNextWindowSize(ImVec2(100, 540));
    IM::BeginStyleVars();
    IM::StyleVar(ImGuiStyleVar_WindowPadding, ImVec2(2.5,5.0));
    IM::StyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    IM::StyleVar(ImGuiStyleVar_FrameRounding, 5);
    
    ImGui::Begin("Cards", nullptr, windowFlags); 
    {
        float dims = std::min(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
        for (CardKey type = CardType::None; type < CardType::COUNT; type++) {
            std::stringstream buttonLabel;
            buttonLabel << Card::TypeName(type);
            ImGui::Button(buttonLabel.str().c_str(), ImVec2(dims, dims));
            
            static bool canCreateCard = true;
            static bool* payloadPtr = &canCreateCard;
            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceNoPreviewTooltip | ImGuiDragDropFlags_AcceptNoDrawDefaultRect)) {
                if (canCreateCard) {
                    Canvas::CVData().HoveredCardID = 
                        Canvas::CVData().Cardmanager->AddCard(type, glm::vec3(Canvas::CVData().WorldMousePos, 1.0f));
                    if (Canvas::CVData().Cardmanager->IsValid(Canvas::CVData().HoveredCardID)) {
                        m_CanvasManager.TransitionTo(Canvas::StateType::DraggCard);
                    }
                    canCreateCard = false;
                }
                ImGui::SetDragDropPayload("CREATE_CARD_BOOL", &payloadPtr, sizeof(payloadPtr));
                ImGui::EndDragDropSource();
            }
        }
    }
    ImGui::End();
    IM::EndStyleVars();
    
    ImGui::SetNextWindowSize(ImVec2(960, 540));
    IM::BeginStyleVars();
    IM::StyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
    IM::StyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    
    ImGui::Begin("Canvas", nullptr, windowFlags);
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
    IM::EndStyleVars();
    
    m_Framebuffer.UnBind();
}


