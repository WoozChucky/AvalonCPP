#include <Engine/Core/Layer.h>

namespace Avalon
{
    Layer::Layer(const std::string& debugName)
            : m_DebugName(debugName)
    {
    }

    Layer::~Layer()
    {
    }
}