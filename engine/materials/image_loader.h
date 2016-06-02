#ifndef IMAGE_LOADER_H_
#define IMAGE_LOADER_H_

#include <FreeImage.h>
#include "../exceptions/file_not_found_exception.h"
#include "../exceptions/unknown_file_type_exception.h"
#include "../exceptions/file_type_not_supported_exception.h"

#pragma comment(lib, "FreeImage.lib")


namespace engine
{
	class ImageLoader;
}

class engine::ImageLoader final
{
public:
	ImageLoader();
	ImageLoader(boost::filesystem::path path);
	~ImageLoader();

	void open(boost::filesystem::path path);
	unsigned getWidth();
	unsigned getHeight();
	unsigned char* getPixels();
	unsigned getSize();
	static ImageLoader& getGlobalInstance();
private:
	ImageLoader(bool global_instance);
	bool m_is_global;

	FIBITMAP* m_bitmap;
	unsigned m_width, m_height;
	unsigned char* m_pixels;
};

#endif
