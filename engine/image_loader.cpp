#include "image_loader.h"
#include "config.h"
#include <boost/filesystem/operations.hpp>

using engine::ImageLoader;


ImageLoader::ImageLoader()
{
	getGlobalInstance();
}

ImageLoader::ImageLoader(boost::filesystem::path path)
	: ImageLoader()
{
	open(path);
}

ImageLoader::ImageLoader(bool global_instance)
	: m_is_global(true)
{
	FreeImage_Initialise();
	Config::getInstance().log(std::string("FreeImage ") + FreeImage_GetVersion() + " loaded");
	Config::getInstance().log(FreeImage_GetCopyrightMessage());
}

ImageLoader::~ImageLoader()
{
	if (m_bitmap != nullptr)
		FreeImage_Unload(m_bitmap);
	if (m_is_global)
	{
		FreeImage_DeInitialise();
		Config::getInstance().log("FreeImage unloaded");
	}
}

void ImageLoader::open(boost::filesystem::path path)
{
	if (!boost::filesystem::exists(path))
		throw FileNotFoundException(path);

	auto path_str = path.string();

	FREE_IMAGE_FORMAT file_format = FreeImage_GetFileType(path_str.c_str());
	if (file_format == FIF_UNKNOWN)
		file_format = FreeImage_GetFIFFromFilename(path_str.c_str());
	if (file_format == FIF_UNKNOWN)
		throw UnknownFileTypeException(path);

	if (!FreeImage_FIFSupportsReading(file_format))
		throw FileTypeNotSupportedException(path);

	m_bitmap = FreeImage_Load(file_format, path_str.c_str());
	if (FreeImage_GetBPP(m_bitmap) != 32)
	{
		FIBITMAP* temp = m_bitmap;
		m_bitmap = FreeImage_ConvertTo32Bits(m_bitmap);
		FreeImage_Unload(temp);
	}
	m_width = FreeImage_GetWidth(m_bitmap);
	m_height = FreeImage_GetHeight(m_bitmap);

	m_pixels = FreeImage_GetBits(m_bitmap);
}

ImageLoader& ImageLoader::getGlobalInstance()
{
	static ImageLoader instance(true);
	return instance;
}

unsigned ImageLoader::getWidth()
{
	return m_width;
}

unsigned ImageLoader::getHeight()
{
	return m_height;
}

unsigned char* ImageLoader::getPixels()
{
	return m_pixels;
}

unsigned ImageLoader::getSize()
{
	return 4 * m_width * m_height;
}