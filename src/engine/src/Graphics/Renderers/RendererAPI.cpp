#include <Engine/Graphics/Renderers/RendererAPI.h>

#include <glad/glad.h>

namespace Avalon
{
    void RendererAPI::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LINE_SMOOTH);
    }

    void RendererAPI::SetViewport(U32 x, U32 y, U32 width, U32 height)
    {
        glViewport(x, y, width, height);
    }

    void RendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, U32 indexCount)
    {
        vertexArray->Bind();
        U32 count = indexCount == 0 ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void RendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, U32 vertexCount)
    {
        vertexArray->Bind();
        glDrawElements(GL_LINES, vertexCount, GL_UNSIGNED_INT, nullptr);
    }

    void RendererAPI::SetLineWidth(F32 width)
    {
        glLineWidth(width);
    }
}