#include "image_loader.hpp"
#include "engine/engine.hpp"


using engine::ImageLoader;


ImageLoader::ImageLoader(const boost::filesystem::path& path)
{
	getStaticInstance();

	auto path_str = path.string().c_str();

	FREE_IMAGE_FORMAT file_format = FreeImage_GetFileType(path_str);
	if (file_format == FIF_UNKNOWN)
		file_format = FreeImage_GetFIFFromFilename(path_str);
	if (file_format == FIF_UNKNOWN)
		throw UnknownFileTypeException(path);

	if (!FreeImage_FIFSupportsReading(file_format))
		throw FileTypeNotSupportedException(path);

	m_bitmap = FreeImage_Load(file_format, path_str);
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

ImageLoader::ImageLoader()
		: m_is_static_instance(true)
{
	FreeImage_Initialise();
	Engine::getInstance().logInfo("FreeImage " + std::string(FreeImage_GetVersion()) + " loaded");
	Engine::getInstance().logInfo(FreeImage_GetCopyrightMessage());
}

ImageLoader::~ImageLoader()
{
	if (m_bitmap != nullptr)
		FreeImage_Unload(m_bitmap);
	if (m_is_static_instance)
	{
		FreeImage_DeInitialise();
		Engine::getInstance().logInfo("FreeImage unloaded");
	}
}

ImageLoader& ImageLoader::getStaticInstance()
{
	static ImageLoader instance;
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
