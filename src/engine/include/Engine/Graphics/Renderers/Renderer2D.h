#pragma once
#include <Common/Types.h>
#include <glm/glm.hpp>

class Renderer2D
{
public:
    static void Init();
    static void Shutdown();

    static void BeginScene(const OrthographicCamera& camera);
    static void EndScene();
    static void Flush();

    static void DrawQuad(const glm::vec2& position,
                         const glm::vec2& size,
                         const glm::vec4& color);
    static void DrawQuad(const glm::vec3& position,
                         const glm::vec2& size,
                         const glm::vec4& color);
    static void DrawQuad(const glm::vec2& position,
                         const glm::vec2& size,
                         const Ref<Texture2D>& texture,
                         F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
    static void DrawQuad(const glm::vec3& position,
                         const glm::vec2& size,
                         const Ref<Texture2D>& texture,
                         F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
    static void DrawQuad(const glm::vec2& position,
                         const glm::vec2& size,
                         const Ref<SubTexture2D>& subtexture,
                         F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
    static void DrawQuad(const glm::vec3& position,
                         const glm::vec2& size,
                         const Ref<SubTexture2D>& subtexture,
                         F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

    static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);
    static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f), int entityID = -1);

    // Rotated Quad
    static void DrawRotatedQuad(const glm::vec2& position,
                                const glm::vec2& size,
                                F32 rotation,
                                const glm::vec4& color);
    static void DrawRotatedQuad(const glm::vec3& position,
                                const glm::vec2& size,
                                F32 rotation,
                                const glm::vec4& color);
    static void DrawRotatedQuad(const glm::vec2& position,
                                const glm::vec2& size,
                                F32 rotation,
                                const Ref<Texture2D>& texture,
                                F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
    static void DrawRotatedQuad(const glm::vec3& position,
                                const glm::vec2& size,
                                F32 rotation,
                                const Ref<Texture2D>& texture,
                                F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
    static void DrawRotatedQuad(const glm::vec2& position,
                                const glm::vec2& size,
                                F32 rotation,
                                const Ref<SubTexture2D>& subtexture,
                                F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
    static void DrawRotatedQuad(const glm::vec3& position,
                                const glm::vec2& size,
                                F32 rotation,
                                const Ref<SubTexture2D>& subtexture,
                                F32 tillingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

    static void DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness = 1.0f, float fade = 0.005f, int entityID = -1);

    static void DrawLine(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color, int entityID = -1);

    static void DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, int entityID = -1);
    static void DrawRect(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);

    struct TextParams
    {
        glm::vec4 Color{ 1.0f };
        float Kerning = 0.0f;
        float LineSpacing = 0.0f;
    };

    //static void DrawString(const std::string& string, Ref<Font> font, const glm::mat4& transform, const TextParams& textParams, int entityID = -1);

    static float GetLineWidth();
    static void SetLineWidth(float width);

    struct Statistics
    {
        U32 DrawCalls = 0;
        U32 QuadCount = 0;

        U32 GetTotalVertexCount() { return QuadCount * 4; }
        U32 GetTotalIndexCount() { return QuadCount * 6; }
    };

    static void ResetStats();
    static Statistics GetStats();

private:
    static void StartBatch();
    static void NextBatch();
};