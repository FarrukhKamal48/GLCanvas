#pragma once
#include <GLBox.h>

class CardTransform {
public:
    glm::vec3 position;
    glm::vec2 scale;
    float rotation;
    glm::vec4 color;
    int cardID;
};

class CardTransform_Manager : public VertexManager {
public:
    CardTransform_Manager() {}
    ~CardTransform_Manager() {}
    uint32_t SizeOfObject()                             const override;
    const VertexBufferLayout MeshLayout()               const override;
    VertexBufferLayout VertLayout(uint32_t divisor)     const override;
    const std::vector<float>& MeshData()                const override;
    const std::vector<uint32_t>& Indicies()             const override;
    const uint32_t AllocateObject(uint32_t count, std::function<void(InstanceRenderer&)> ConfigureShader) const override;
    
    CardTransform& operator[](uint32_t i);
private:
    inline static const std::vector<float> m_Mesh = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
    };
    inline static const std::vector<uint32_t> m_Indicies = {
        0, 1, 2, 
        0, 2, 3
    };
public:
    inline static std::vector<CardTransform> m_Instances = {};
    inline static int m_RendererI = -1;
};

