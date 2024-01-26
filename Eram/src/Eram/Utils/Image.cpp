#include "erpch.h"
#include "Image.h"

#include <stb_image.h>

namespace Eram
{

	Image::Image(const std::string filePath, bool flipImage)
	{
		ER_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(flipImage);
		ImageData = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

		if (ImageData)
		{
			Width = (uint32_t)width;
			Height = (uint32_t)height;

			if (channels == 2)
			{
				Format = ImageFormat::RG8;
			}

			else if (channels == 3)
			{
				Format = ImageFormat::RGB8;
			}

			else if (channels == 4)
			{
				Format = ImageFormat::RGBA8;
			}

			else
			{
				ER_ERROR("Unable to load image: Image format not supported");
			}

			Size = Width * Utils::ImageFormatToSize(Format) * Height;
		}

		else
		{
			ER_ERROR("Failed to load image: {0}", filePath);
		}
	}

	Image::Image(uint32_t width, uint32_t height, ImageFormat format)
		: Width(width), Height(height), Format(format)
	{
		Size = Width * Utils::ImageFormatToSize(Format) * Height;
		ImageData = new uint8_t[Size];
	}

	Image::~Image()
	{
		delete[] ImageData;
	}

	void Image::FlipVerticaly()
	{
		ER_PROFILE_FUNCTION();

		uint32_t bufferWidth = Width * Utils::ImageFormatToSize(Format);
		uint8_t* buffer = new uint8_t[bufferWidth];

		uint32_t endIndex = Height - 1;
		for (uint32_t i = 0; i < Height / 2; i++)
		{
			memcpy(buffer, ImageData + i * bufferWidth, bufferWidth);
			memcpy(ImageData + i * bufferWidth, ImageData + (endIndex - i) * bufferWidth, bufferWidth);
			memcpy(ImageData + (endIndex - i) * bufferWidth, buffer, bufferWidth);
		}

		delete[] buffer;
	}

	namespace Utils
	{
		uint32_t ImageFormatToSize(ImageFormat imageFormat)
		{
			switch (imageFormat)
			{
				case Eram::ImageFormat::None:    return 0;
				case Eram::ImageFormat::R8:      return 1;
				case Eram::ImageFormat::RG8:     return 2;
				case Eram::ImageFormat::RGB8:    return 3;
				case Eram::ImageFormat::RGBA8:   return 4;
				case Eram::ImageFormat::RGBA32F: return 4 * sizeof(float);
				default:                         return 0;
			}
		}

		std::string ImageFormatToString(ImageFormat imageFormat)
		{
			switch (imageFormat)
			{
				case Eram::ImageFormat::None:    return "None";
				case Eram::ImageFormat::R8:      return "R8";
				case Eram::ImageFormat::RG8:     return "RG8";
				case Eram::ImageFormat::RGB8:    return "RGB8";
				case Eram::ImageFormat::RGBA8:   return "RGBA8";
				case Eram::ImageFormat::RGBA32F: return "RGBA32F";
				default:                         return "Invalid";
			}
		}

	}

}