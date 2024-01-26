#pragma once

#include "Eram/Renderer/Buffer.h"

namespace Eram {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(void* verticies, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual void Resize(uint32_t size) override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; };
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indecies, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const;

		virtual void Resize(uint32_t* indecies, uint32_t count) override;

		virtual uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}