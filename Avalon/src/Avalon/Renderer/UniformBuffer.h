#pragma once

#include "Avalon/Core/Base.h"

namespace Avalon
{
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() = default;

		virtual void SetData(const void* data, U32 size, U32 offset = 0) = 0;

		static Ref<UniformBuffer> Create(U32 size, U32 binding);
	};
}