#pragma once

#include "Eram/Renderer/Texture.h"

#include <glad/glad.h>

namespace Eram
{

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(Image& image);
		OpenGLTexture2D(const std::string& filepath);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; };
		virtual uint32_t GetRendererID() const override { return m_RendererID; };

		virtual const std::string& GetFilepath() const override { return m_Filepath; };

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool IsLoaded() const override { return m_IsLoaded; }
	private:
		void CreateTexture(Image& image);
	private:
		std::string m_Filepath;
		bool m_IsLoaded = false;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};

}