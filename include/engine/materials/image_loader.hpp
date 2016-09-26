#ifndef IMAGE_LOADER_HPP_
#define IMAGE_LOADER_HPP_

#include <FreeImage.h>
#include "../exceptions/file_not_found_exception.hpp"
#include "../exceptions/unknown_file_type_exception.hpp"
#include "../exceptions/file_type_not_supported_exception.hpp"

#pragma comment(lib, "FreeImage.lib")


namespace engine
{
	class ImageLoader;
}

class engine::ImageLoader final
{
public:
	ImageLoader();
	ImageLoader(const boost::filesystem::path& path);
	~ImageLoader();

	unsigned getWidth() const;
	unsigned getHeight() const;
	unsigned char* getPixels() const;
	unsigned getSize() const;
	static ImageLoader& getGlobalInstance();
private:
	ImageLoader(const bool& global_instance);
	bool m_is_global = false;

	FIBITMAP* m_bitmap;
	unsigned m_width, m_height;
	unsigned char* m_pixels;
};

#endif /* IMAGE_LOADER_HPP_ */
