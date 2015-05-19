#include "Texture.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

namespace smoke
{

	Texture::Texture( const std::string& fileName ) : m_bpp(0), m_width(0), m_height(0), m_format(0)
	{
		load(fileName);
	}

	Texture::~Texture()
	{
		ilDeleteImages(1, &ILImage);
	}

	void Texture::load(const std::string& fileName)
	{
		ILImage;
		ilGenImages(1,&ILImage);

		ilBindImage(ILImage);
		ILboolean success = ilLoadImage((const ILstring)fileName.c_str());

		if (!success)
		{
			ilDeleteImages(1, &ILImage);
			return;
		}

		m_bpp = ilGetInteger(IL_IMAGE_BPP);
		m_width = ilGetInteger(IL_IMAGE_WIDTH);
		m_height = ilGetInteger(IL_IMAGE_HEIGHT);
		m_format = ilGetInteger(IL_IMAGE_FORMAT);
		std::size_t dataSize = m_height * m_width * sizeof(unsigned char);
	}

	int Texture::getImageFormat() const
	{
		return m_format;
	}

	int Texture::getBPP() const
	{
		return m_bpp;
	}

	int Texture::getWidth() const
	{
		return m_width;
	}

	int Texture::getHeight() const
	{
		return m_height;
	}

	const void* Texture::getImageData() const
	{
		return ilGetData();
	}

}