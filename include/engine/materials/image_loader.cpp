#include "image_loader.hpp"
#include "../config.hpp"
#include <boost/filesystem/operations.hpp>

using engine::ImageLoader;


ImageLoader::ImageLoader()
{
	getGlobalInstance();
}

ImageLoader::ImageLoader(const boost::filesystem::path& path)
	: ImageLoader()
{
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

ImageLoader::ImageLoader(const bool& global_instance)
	: m_is_global(true)
{
	FreeImage_Initialise();
	Config::getInstance().logInfo(std::string("FreeImage ") + FreeImage_GetVersion() + " loaded");
	Config::getInstance().logInfo(FreeImage_GetCopyrightMessage());
}

ImageLoader::~ImageLoader()
{
	if (m_bitmap != nullptr)
		FreeImage_Unload(m_bitmap);
	if (m_is_global)
	{
		FreeImage_DeInitialise();
		Config::getInstance().logInfo(std::string("FreeImage ") + FreeImage_GetVersion() + " unloaded");
	}
}

ImageLoader& ImageLoader::getGlobalInstance()
{
	static ImageLoader instance(true);
	return instance;
}

unsigned ImageLoader::getWidth() const
{
	return m_width;
}

unsigned ImageLoader::getHeight() const
{
	return m_height;
}

unsigned char* ImageLoader::getPixels() const
{
	return m_pixels;
}

unsigned ImageLoader::getSize() const
{
	return 4 * m_width * m_height;
}
