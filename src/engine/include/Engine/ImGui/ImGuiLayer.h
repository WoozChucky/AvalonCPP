#pragma once

#include <Engine/Core/Layer.h>

namespace Avalon {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event& event) override;

        void Begin();
        void End();

    private:
        F32 m_Time = 0.0f;
    };

}