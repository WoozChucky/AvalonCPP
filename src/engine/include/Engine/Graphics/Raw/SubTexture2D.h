#pragma once

#include <Engine/Graphics/Raw/Texture2D.h>

#include <glm/glm.hpp>

namespace Avalon
{
    class SubTexture2D
    {
    public:
        SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max) :
                m_Texture(texture)
        {
            m_TexCoords[0] = { min.x, min.y };
            m_TexCoords[1] = { max.x, min.y };
            m_TexCoords[2] = { max.x, max.y };
            m_TexCoords[3] = { min.x, max.y };
        }

        const Ref<Texture2D> GetTexture() const { return m_Texture; }
        const glm::vec2* GetTexCoords() const { return m_TexCoords; }

        static Ref<SubTexture2D> CreateFromCoords(
                const Ref<Texture2D>& texture,
                const glm::vec2& coords,
                const glm::vec2& cellSize,
                const glm::vec2& spriteSize = { 1.0f, 1.0f }
        ) {
            glm::vec2 min = {
                    (coords.x * cellSize.x) / texture->GetWidth(),
                    (coords.y * cellSize.y) / texture->GetHeight()
            };

            glm::vec2 max = {
                    ((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(),
                    ((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight()
            };

            return CreateRef<SubTexture2D>(texture, min, max);
        }

    private:
        Ref<Texture2D> m_Texture;
        glm::vec2 m_TexCoords[4];
    };
}