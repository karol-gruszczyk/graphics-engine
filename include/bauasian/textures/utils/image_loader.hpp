#ifndef BAUASIAN_IMAGE_LOADER_HPP
#define BAUASIAN_IMAGE_LOADER_HPP

#include "bauasian/exceptions/file_not_found_exception.hpp"
#include "bauasian/exceptions/unknown_file_type_exception.hpp"
#include "bauasian/exceptions/file_type_not_supported_exception.hpp"

#include <FreeImage.h>
#include <glm/glm.hpp>


namespace bauasian
{
	class ImageLoader;
}

class bauasian::ImageLoader final
{
public:
	ImageLoader(const boost::filesystem::path& path, unsigned num_rotate_sides = 0);
	~ImageLoader();

	const glm::uvec2& getSize() const
	{ return m_size; }
	unsigned char* getPixels() const
	{ return m_pixels; }
	unsigned getBitsPerPixel() const
	{ return m_bits_per_pixel; }

private:
	ImageLoader();

	bool m_is_static_instance = false;
	FIBITMAP* m_bitmap;
	glm::uvec2 m_size;
	unsigned char* m_pixels;
	unsigned m_bits_per_pixel;

	static ImageLoader& getStaticInstance();
};

#endif /* BAUASIAN_IMAGE_LOADER_HPP */
