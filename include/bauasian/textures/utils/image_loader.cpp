#include "image_loader.hpp"
#include "bauasian/bauasian.hpp"


using bauasian::ImageLoader;


ImageLoader::ImageLoader(const boost::filesystem::path& path, unsigned num_rotate_sides)
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
	if (FreeImage_GetBPP(m_bitmap) > 32)
	{
		FIBITMAP* temp = m_bitmap;
		m_bitmap = FreeImage_ConvertTo32Bits(m_bitmap);
		FreeImage_Unload(temp);
	}
	else if (FreeImage_GetBPP(m_bitmap) < 8)
	{
		FIBITMAP* temp = m_bitmap;
		m_bitmap = FreeImage_ConvertTo8Bits(m_bitmap);
		FreeImage_Unload(temp);
	}
	m_bits_per_pixel = FreeImage_GetBPP(m_bitmap);
	if (num_rotate_sides)
		m_bitmap = FreeImage_Rotate(m_bitmap, num_rotate_sides * 90);
	m_size.x = FreeImage_GetWidth(m_bitmap);
	m_size.y = FreeImage_GetHeight(m_bitmap);

	m_pixels = FreeImage_GetBits(m_bitmap);
}

ImageLoader::ImageLoader()
		: m_is_static_instance(true)
{
	FreeImage_Initialise();
	Bauasian::getInstance().logInfo("FreeImage " + std::string(FreeImage_GetVersion()) + " loaded");
	Bauasian::getInstance().logInfo(FreeImage_GetCopyrightMessage());
}

ImageLoader::~ImageLoader()
{
	if (m_bitmap != nullptr)
		FreeImage_Unload(m_bitmap);
	if (m_is_static_instance)
	{
		FreeImage_DeInitialise();
		Bauasian::getInstance().logInfo("FreeImage unloaded");
	}
}

ImageLoader& ImageLoader::getStaticInstance()
{
	static ImageLoader instance;
	return instance;
}
