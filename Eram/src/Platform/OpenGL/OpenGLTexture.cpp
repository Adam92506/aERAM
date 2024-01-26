#include "erpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

#include "Eram/Utils/Image.h"

namespace Eram
{

	namespace Utils
	{

		static GLenum EramImageFormatToGLDataFormat(ImageFormat format)
		{
			switch (format)
			{
				case ImageFormat::RG8: return GL_RG;
				case ImageFormat::RGB8: return GL_RGB;
				case ImageFormat::RGBA8: return GL_RGBA;
				case ImageFormat::RGBA32F: return GL_RGBA;
			}

			ER_ASSERT(false, "Image format not supported");
			return 0;
		}

		static GLenum EramImageFormatToGLInternalFormat(ImageFormat format)
		{
			switch (format)
			{
				case ImageFormat::RG8: return GL_RG8;
				case ImageFormat::RGB8: return GL_RGB8;
				case ImageFormat::RGBA8: return GL_RGBA8;
				case ImageFormat::RGBA32F: return GL_RGBA32F;
			}

			ER_ASSERT(false, "Image format not supported");
			return 0;
		}

	}

	OpenGLTexture2D::OpenGLTexture2D(Image& image)
	{
		if (image.ImageData)
		{
			CreateTexture(image);
		}
	}


	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
		: m_Filepath(filepath)
	{
		ER_PROFILE_FUNCTION();

		Image image(filepath, true);

		if (image.ImageData)
		{
			CreateTexture(image);
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		ER_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::CreateTexture(Image& image)
	{
		ER_PROFILE_FUNCTION();

		m_IsLoaded = true;

		m_Width = image.Height;
		m_Height = image.Width;

		m_InternalFormat = Utils::EramImageFormatToGLInternalFormat(image.Format);
		m_DataFormat = Utils::EramImageFormatToGLDataFormat(image.Format);

		ER_ASSERT(m_InternalFormat & m_DataFormat, "Image format not supported");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, image.ImageData);
	}

}