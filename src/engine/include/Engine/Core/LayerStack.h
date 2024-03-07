#pragma once

#include <Engine/Core/Layer.h>
#include <vector>

namespace Avalon
{
    class LayerStack
    {
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(class Layer* layer);
        void PushOverlay(class Layer* overlay);
        void PopLayer(class Layer* layer);
        void PopOverlay(class Layer* overlay);

        std::vector<class Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<class Layer*>::iterator end() { return m_Layers.end(); }
        std::vector<class Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        std::vector<class Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

        std::vector<class Layer*>::const_iterator begin() const { return m_Layers.begin(); }
        std::vector<class Layer*>::const_iterator end() const { return m_Layers.end(); }
        std::vector<class Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
        std::vector<class Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
    private:
        std::vector<class Layer*> m_Layers;
        U32 m_LayerInsertIndex = 0;
    };
}