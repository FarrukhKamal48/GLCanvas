#include "GLCanvas/ImVec2Extend.h"
#include "GLCanvas/Canvas/Canvas.h"

#define PI glm::pi<float>()

Canvas::Canvas()
    : m_CameraController(16.0f/9.0f, 1.0f) 
{ }
Canvas::~Canvas() {}
    
void Canvas::OnEvent(Event& event) {
    m_CameraController.OnEvent(event);
}

void Canvas::OnAttach() {
    m_BackgroundI = m_Manager.AllocateObject(10, [](InstanceRenderer& renderer) {
        renderer.CreateShader("GLBox/assets/shaders/instancing/RotationQuad.vert", 
                              "GLBox/assets/shaders/instancing/RotationQuad.frag");
    });
    
    for (int i = 0; i < 10; i++) {
        m_Manager[m_BackgroundI+i].position = glm::vec3(glm::cos(i), glm::sin(i), -1);
        m_Manager[m_BackgroundI+i].scale = glm::vec2(0.05);
        m_Manager[m_BackgroundI+i].rotation = PI/4;
        m_Manager[m_BackgroundI+i].color = glm::vec4(i/10.0f, glm::sin(i), i/15.0f, 1.0f);
    }

    m_Manager[m_BackgroundI].position = {0,0,1};
    m_Manager[m_BackgroundI].scale = glm::vec2(0.05);
    m_Manager[m_BackgroundI].rotation = PI/4;
    m_Manager[m_BackgroundI].color = glm::vec4(0,0,0,1);
}

glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float p) {
    return a + p * (b-a);
}

void Canvas::OnUpdate(float dt) {
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
    
    m_Manager[m_BackgroundI].position = glm::vec3(m_WorldMousePos, 0.0f);
    m_Manager[m_BackgroundI].rotation += 5 * dt;
}
void Canvas::OnImGuiRender() {
    m_WindowMousePos = ImGui::GetMousePos() - ImGui::GetWindowPos() 
        - ImVec2(0, ImGui::GetWindowHeight() - m_ViewportSize.y);
    
    ImGui::GetWindowDrawList()->AddCircleFilled(
        WorldToScreen(m_WorldMousePos), 
        10 / m_CameraController.GetZoomLevel(), 
        IM_COL32(255, 255, 0, 255)
    );

    m_CardManager.OnImGuiRender();
}

void Canvas::OnViewportResize(glm::vec2 size) {
    m_ViewportSize = size;
    m_CameraController.OnResize(size.x, size.y);
}


glm::vec2 Canvas::ScreenToWorld(ImVec2 screenCoords) {
    return glm::vec2(
        screenCoords.x/m_ViewportSize.x - 0.5f,
        1.0f - screenCoords.y/m_ViewportSize.y - 0.5f
    ) * m_CameraController.GetBounds() + glm::vec2(m_CameraController.GetCamera().GetPosition());
}

ImVec2 Canvas::WorldToScreen(glm::vec2 worldCoords) {
    return glm::vec2(
        0.5f + (worldCoords.x - m_CameraController.GetCamera().GetPosition().x)/m_CameraController.GetBounds().x,
        0.5f - (worldCoords.y - m_CameraController.GetCamera().GetPosition().y)/m_CameraController.GetBounds().y
    ) * m_ViewportSize + ImGui::GetWindowPos() + glm::vec2(0, ImGui::GetWindowHeight() - m_ViewportSize.y);
}
