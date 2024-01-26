#include "erpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Eram {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:  return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Mat3:   return GL_FLOAT;
			case ShaderDataType::Mat4:   return GL_FLOAT;
			case ShaderDataType::Int:    return GL_INT;
			case ShaderDataType::Int2:   return GL_INT;
			case ShaderDataType::Int3:   return GL_INT;
			case ShaderDataType::Int4:   return GL_INT;
			case ShaderDataType::UInt:    return GL_UNSIGNED_INT;
			case ShaderDataType::UInt2:   return GL_UNSIGNED_INT;
			case ShaderDataType::UInt3:   return GL_UNSIGNED_INT;
			case ShaderDataType::UInt4:   return GL_UNSIGNED_INT;
			case ShaderDataType::Bool:   return GL_BOOL;
		}

		ER_ASSERT(false, "Unknown ShaderDataType");
		return GL_NONE;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		ER_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		ER_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> vertexBuffer)
	{
		ER_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		ER_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				{
					glEnableVertexAttribArray(m_AttributeIndex);
					glVertexAttribPointer(m_AttributeIndex,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.Offset);
					m_AttributeIndex++;
					break;
				}
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::UInt:
				case ShaderDataType::UInt2:
				case ShaderDataType::UInt3:
				case ShaderDataType::UInt4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(m_AttributeIndex);
					glVertexAttribIPointer(m_AttributeIndex,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(element.Type),
						layout.GetStride(),
						(const void*)element.Offset);
					m_AttributeIndex++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					uint8_t count = element.GetComponentCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(m_AttributeIndex);
						glVertexAttribPointer(m_AttributeIndex,
							count,
							ShaderDataTypeToOpenGLBaseType(element.Type),
							element.Normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride(),
							(const void*)(element.Offset + sizeof(float) * count * i));
						glVertexAttribDivisor(m_AttributeIndex, 1);
						m_AttributeIndex++;
					}
					break;
				}
				default: ER_ASSERT(false, "Unknown ShaderDataType");
			}
			
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> indexBuffer)
	{
		ER_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}


}