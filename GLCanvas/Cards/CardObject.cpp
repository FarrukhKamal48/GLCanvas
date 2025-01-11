#include "GLCanvas/Cards/CardObject.h"

template<>
void VertexBufferLayout::Push<int>(uint32_t count, uint32_t divisor) {
    m_Elements.push_back({ count, GL_INT, GL_FALSE, divisor });
    m_Stride += count * VertexBufferLayoutElement::SizeOf(GL_INT);
}

uint32_t CardTransform_Manager::SizeOfObject()                             const { return sizeof(CardTransform); }
const VertexBufferLayout CardTransform_Manager::MeshLayout()               const { 
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    return layout;
}
VertexBufferLayout CardTransform_Manager::VertLayout(uint32_t divisor)     const { 
    VertexBufferLayout layout;
    layout.Push<float>(3, divisor);
    layout.Push<float>(2, divisor);
    layout.Push<float>(1, divisor);
    layout.Push<float>(4, divisor);
    layout.Push<int>(1, divisor);
    return layout;
}
const std::vector<float>& CardTransform_Manager::MeshData()                const { return m_Mesh; }
const std::vector<uint32_t>& CardTransform_Manager::Indicies()             const { return m_Indicies; }
const uint32_t CardTransform_Manager::AllocateObject(uint32_t count, std::function<void(InstanceRenderer&)> ConfigureShader) const {
    return InstanceRenderer::AllocateObj(count, ConfigureShader, new CardTransform_Manager(), m_Instances, m_RendererI);
}

CardTransform& CardTransform_Manager::operator[](uint32_t i) {
    assert(i >= 0 && i < m_Instances.size() 
           && "Invalid index into QuadTransform_Manager::m_Instances");
    return m_Instances[i]; 
}
