#pragma once

#include <Common/Types.h>
#include <Engine/Graphics/Renderers/RendererAPI.h>
#include <Engine/Graphics/OrthographicCamera.h>
#include <Engine/Graphics/Raw/Shader.h>
#include "Renderer2D.h"

namespace Avalon
{
    class Renderer
    {
    public:

        static void Init() {
            RendererAPI::Init();
            Renderer2D::Init();
        }
        static void Shutdown() {
            Renderer2D::Shutdown();
        }

        static void OnWindowResize(U32 width, U32 height) {
            RendererAPI::SetViewport(0, 0, width, height);
        }

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static Scope<SceneData> s_SceneData;
    };
}