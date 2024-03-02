#pragma once

#include "Avalon/Core/Base.h"

#include <string>

namespace Avalon
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual U32 GetWidth() const = 0;
		virtual U32 GetHeight() const = 0;
		virtual U32 GetRendererID() const = 0;

		virtual void SetData(void* data, U32 size) = 0;

		virtual void Bind(U32 slot = 0) const = 0;
		virtual void Unbind(U32 slot = 0) const = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(U32 width, U32 height);
		static Ref<Texture2D> Create(const std::string& path);
	};
}