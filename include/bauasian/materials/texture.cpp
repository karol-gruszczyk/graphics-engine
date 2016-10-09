#include "texture.hpp"
#include "image_loader.hpp"
#include "bauasian/bauasian.hpp"
#include "bauasian/exceptions/unknown_extension_exception.hpp"

#include <sstream>


using bauasian::Texture;


Texture::Texture(const unsigned& width, const unsigned& height, const GLubyte* const pixels,
                 const GLint& internal_format, const GLenum& format, const bool& generate_mipmaps,
                 std::string image_name /* = "" */)
{
	m_width = width;
	m_height = height;

	auto is_power_of_2 = [](unsigned number) -> bool { return !(number & (number - 1)); };
	if (!is_power_of_2(m_width) || !is_power_of_2(m_height))
	{
		if (image_name.empty())
		{
			std::stringstream ss;
			ss << (void*) pixels;
			image_name = "In memory object at 0x" + ss.str();
		}
		auto dimensions = std::to_string(m_width) + " x " + std::to_string(m_height);
		bauasian::Bauasian::getInstance().logWarning(
				"Performance warning, image '" + image_name + "' - dimensions " + dimensions + " are not a power of 2");
	}

	glGenTextures(1, &m_texture_id);
	glTextureImage2DEXT(m_texture_id, GL_TEXTURE_2D, 0, internal_format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE,
	                    pixels);

	if (generate_mipmaps)
	{
		glGenerateTextureMipmap(m_texture_id);
		// TODO: try something better
		if (glewIsExtensionSupported("GL_EXT_texture_filter_anisotropic"))
		{
			GLfloat max_anisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
			glTextureParameterf(m_texture_id, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
		}
	}

	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(m_texture_id, GL_TEXTURE_MIN_FILTER,
	                    generate_mipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
	glTextureParameteri(m_texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(const unsigned& width, const unsigned& height, const GLint& internal_format, const GLenum& format)
		: m_width(width), m_height(height)
{
	glGenTextures(1, &m_texture_id);
	glTextureImage2DEXT(m_texture_id, GL_TEXTURE_2D, 0, internal_format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE,
	                    nullptr);

	glTextureParameteri(m_texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
}

Texture::~Texture()
{
	if (m_texture_id)
		glDeleteTextures(1, &m_texture_id);
}

void Texture::update(const unsigned& width, const unsigned& height, const GLint& internal_format, const GLenum& format)
{
	m_width = width;
	m_height = height;
	glTextureImage2DEXT(m_texture_id, GL_TEXTURE_2D, 0, internal_format, m_width, m_height, 0, format,
	                    GL_UNSIGNED_BYTE, nullptr);
}

void Texture::save(const boost::filesystem::path& path)
{
	auto fif = FreeImage_GetFIFFromFilename(path.filename().c_str());
	if (fif == FIF_UNKNOWN)
		throw UnknownExtensionException(path.filename().string());

	unsigned channels = 4;
	GLenum format = GL_BGRA;
	if (fif == FIF_JPEG)
	{
		channels = 3;
		format = GL_BGR;
	}
	GLubyte* pixels = new GLubyte[channels * m_width * m_height];

	glGetTextureImageEXT(m_texture_id, GL_TEXTURE_2D, 0, format, GL_UNSIGNED_BYTE, pixels);

	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, m_width, m_height,
	                                               channels * m_width, channels * 8,
	                                               FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK,
	                                               FALSE);
	FreeImage_Save(fif, image, path.c_str());

	FreeImage_Unload(image);
	delete[] pixels;
}

void Texture::bind(unsigned short texture_level /* = 0 */) const
{
	glActiveTexture(GL_TEXTURE0 + texture_level);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

const GLuint& Texture::getTextureId() const
{
	return m_texture_id;
}
