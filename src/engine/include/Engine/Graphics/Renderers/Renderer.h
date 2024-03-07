#pragma once

#include <Common/Types.h>
#include <Engine/Graphics/Renderers/RendererAPI.h>
#include <Engine/Graphics/OrthographicCamera.h>
#include <Engine/Graphics/Raw/Shader.h>

namespace Avalon
{
    class Renderer
    {
    public:

        static void Init() {

        }
        static void Shutdown() {

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