#ifndef _Texture_
#define _Texture_

#include <string>

namespace smoke
{
	class Texture
	{
	public:
		Texture(const std::string& fileName);
		~Texture();
		int getImageFormat() const;
		int getBPP() const;
		int getWidth() const;
		int getHeight() const;
		const void* getImageData() const;

	private:
		void load(const std::string& fileName);

		int m_bpp;
		int m_format;
		int m_width;
		int m_height;
		unsigned int ILImage;
	};
}

#endif