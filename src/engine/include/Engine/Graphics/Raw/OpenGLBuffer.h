#pragma once

#include <Common/Types.h>

enum class ShaderDataType : U8
{
    None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static U32 ShaderDataTypeSize(ShaderDataType type)
{
    switch (type)
    {
        case ShaderDataType::Float:		return 4;
        case ShaderDataType::Float2:	return 4 * 2;
        case ShaderDataType::Float3:	return 4 * 3;
        case ShaderDataType::Float4:	return 4 * 4;
        case ShaderDataType::Mat3:		return 4 * 3 * 3;
        case ShaderDataType::Mat4:		return 4 * 4 * 4;
        case ShaderDataType::Int:		return 4;
        case ShaderDataType::Int2:		return 4 * 2;
        case ShaderDataType::Int3:		return 4 * 3;
        case ShaderDataType::Int4:		return 4 * 4;
        case ShaderDataType::Bool:		return 1;
    }

    throw std::runtime_error("Unknown ShaderDataType");
}

struct BufferElement
{
    std::string Name;
    ShaderDataType Type;
    U32 Offset;
    U32 Size;
    bool Normalized;

    BufferElement() = default;

    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Offset(0), Size(ShaderDataTypeSize(type)), Normalized(normalized)
    {
    }

    U32 GetComponentCount() const
    {
        switch (Type)
        {
            case ShaderDataType::Float:		return 1;
            case ShaderDataType::Float2:	return 2;
            case ShaderDataType::Float3:	return 3;
            case ShaderDataType::Float4:	return 4;
            case ShaderDataType::Mat3:		return 3 * 3;
            case ShaderDataType::Mat4:		return 4 * 4;
            case ShaderDataType::Int:		return 1;
            case ShaderDataType::Int2:		return 2;
            case ShaderDataType::Int3:		return 3;
            case ShaderDataType::Int4:		return 4;
            case ShaderDataType::Bool:		return 1;
        }

        throw std::runtime_error("Unknown ShaderDataType");
        return 0;
    }
};

class BufferLayout
{
public:
    BufferLayout() {}
    BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_Elements(elements)
    {
        CalculateOffsetsAndStride();
    }

    inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
    inline U32 GetStride() const { return m_Stride; }

    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

private:
    std::vector<BufferElement> m_Elements;
    U32 m_Stride = 0;

    void CalculateOffsetsAndStride()
    {
        U32 offset = 0;
        m_Stride = 0;
        for (auto& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }
};