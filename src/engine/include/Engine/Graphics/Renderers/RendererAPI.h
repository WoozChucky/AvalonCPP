#pragma once

#include <Engine/Graphics/Raw/VertexArray.h>
#include <glm/glm.hpp>

namespace Avalon
{
    class RendererAPI
    {
    public:
        static void Init();
        static void SetClearColor(const glm::vec4& color);
        static void Clear();

        static void SetViewport(U32 x, U32 y, U32 width, U32 height);

        static void DrawIndexed(const Ref<VertexArray>& vertexArray, U32 indexCount = 0);
        static void DrawLines(const Ref<VertexArray>& vertexArray, U32 vertexCount);

        static void SetLineWidth(F32 width);
    };
}