#ifndef BAUASIAN_IMAGE_LOADER_HPP
#define BAUASIAN_IMAGE_LOADER_HPP

#include "bauasian/exceptions/file_not_found_exception.hpp"
#include "bauasian/exceptions/unknown_file_type_exception.hpp"
#include "bauasian/exceptions/file_type_not_supported_exception.hpp"

#include <FreeImage.h>


namespace bauasian
{
	class ImageLoader;
}

class bauasian::ImageLoader final
{
public:
	ImageLoader(const boost::filesystem::path& path, const unsigned& num_rotate_sides = 0);
	~ImageLoader();

	unsigned getWidth() const;
	unsigned getHeight() const;
	unsigned char* getPixels() const;
	unsigned getSize() const;

private:
	ImageLoader();

	bool m_is_static_instance = false;
	FIBITMAP* m_bitmap;
	unsigned m_width, m_height;
	unsigned char* m_pixels;

	static ImageLoader& getStaticInstance();
};

#endif /* BAUASIAN_IMAGE_LOADER_HPP */
