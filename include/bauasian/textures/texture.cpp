#include "texture.hpp"
#include "bauasian/textures/utils/image_loader.hpp"
#include "bauasian/bauasian.hpp"
#include "bauasian/open_gl_extensions.hpp"
#include "bauasian/exceptions/unknown_extension_exception.hpp"

#include <sstream>


using bauasian::Texture;

Texture::Texture(const glm::uvec2& size, const void* pixels, GLint internal_format,
				 GLenum format, bool generate_mipmaps, std::string image_name, GLenum type)
		: TextureMixin(GL_TEXTURE_2D, internal_format, format), FrameBufferAttachment(size)
{
	auto is_power_of_2 = [](unsigned number) -> bool { return !(number & (number - 1)); };
	if (!is_power_of_2(m_size.x) || !is_power_of_2(m_size.y))
	{
		if (image_name.empty())
		{
			std::stringstream ss;
			ss << (void*) pixels;
			image_name = "In memory object at 0x" + ss.str();
		}
		auto dimensions = std::to_string(m_size.x) + " x " + std::to_string(m_size.y);
		bauasian::Bauasian::getInstance().logWarning(
				"Performance warning, image '" + image_name + "' - dimensions " + dimensions + " are not a power of 2");
	}

	glTextureImage2DEXT(m_texture_id, GL_TEXTURE_2D, 0, internal_format, m_size.x, m_size.y,
	                    0, format, type, pixels);

	if (generate_mipmaps)
	{
		glGenerateTextureMipmap(m_texture_id);

		if (OpenGLExtensions::getInstance().isAnisotropicFilteringSupported())
			glTextureParameterf(m_texture_id, GL_TEXTURE_MAX_ANISOTROPY_EXT,
			                    OpenGLExtensions::getInstance().getMaxAnisotropy());
	}

	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(m_texture_id, GL_TEXTURE_MIN_FILTER, generate_mipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
	glTextureParameteri(m_texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(GLint internal_format, GLenum format, glm::uvec2 size, GLenum type)
		: TextureMixin(GL_TEXTURE_2D, internal_format, format), FrameBufferAttachment(size)
{
	glTextureImage2DEXT(m_texture_id, GL_TEXTURE_2D, 0, internal_format, m_size.x, m_size.y,
	                    0, format, type, nullptr);

	glTextureParameteri(m_texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
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
	GLubyte* pixels = new GLubyte[channels * m_size.x * m_size.y];

	glGetTextureImageEXT(m_texture_id, GL_TEXTURE_2D, 0, format, GL_UNSIGNED_BYTE, pixels);

	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, m_size.x, m_size.y,
	                                               channels * m_size.x, channels * 8,
	                                               FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK,
	                                               FALSE);
	FreeImage_Save(fif, image, path.c_str());

	FreeImage_Unload(image);
	delete[] pixels;
}

void Texture::setSize(const glm::uvec2& size)
{
	FrameBufferAttachment::setSize(size);
	glTextureImage2DEXT(m_texture_id, GL_TEXTURE_2D, 0, m_internal_format, m_size.x, m_size.y,
						0, m_format, GL_UNSIGNED_BYTE, nullptr);
}

void Texture::setFiltering(GLenum filtering) const
{
	glTextureParameteri(m_texture_id, GL_TEXTURE_MIN_FILTER, filtering);
	glTextureParameteri(m_texture_id, GL_TEXTURE_MAG_FILTER, filtering);
}

void Texture::enableDepthComparison() const
{
	glTextureParameteri(m_texture_id, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
}
