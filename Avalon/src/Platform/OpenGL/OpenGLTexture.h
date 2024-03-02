#pragma once

#include "Avalon/Renderer/Texture.h"

namespace Avalon
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(U32 width, U32 height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual U32 GetWidth() const override { return m_Width; }
		virtual U32 GetHeight() const override { return m_Height; }
		virtual U32 GetRendererID() const override { return m_RendererID; }

		virtual void SetData(void* data, U32 size) override;

		virtual void Bind(U32 slot = 0) const override;
		virtual void Unbind(U32 slot = 0) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

	private:
		std::string m_Path;
		U32 m_Width, m_Height;
		U32 m_RendererID;
		U32 m_InternalFormat, m_DataFormat;

	};
}