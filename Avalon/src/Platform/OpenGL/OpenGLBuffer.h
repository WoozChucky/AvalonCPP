#pragma once

#include "Avalon/Core/Base.h"
#include "Avalon/Renderer/Buffer.h"

namespace Avalon
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(U32 size);
		OpenGLVertexBuffer(F32* vertices, U32 size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, U32 size) override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		U32 m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(U32* indices, U32 count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual U32 GetCount() const override;
	private:
		U32 m_RendererID;
		U16 m_Count;
	};
}