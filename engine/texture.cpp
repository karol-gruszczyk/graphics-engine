#include "texture.h"
#include "config.h"
#include "image_loader.h"
#include <boost/lexical_cast.hpp>

using engine::Texture;


Texture::Texture()
{}

Texture::Texture(boost::filesystem::path path)
{
	loadFromFile(path);
}

Texture::Texture(unsigned width, unsigned height, GLubyte* pixels, GLint internal_format, GLenum format, bool generate_mipmaps)
{
	loadFromMemory(width, height, pixels, internal_format, format, generate_mipmaps);
}

Texture::~Texture()
{
	if (m_texture_created)
		glDeleteTextures(1, &m_texture_id);
}

void Texture::loadFromFile(boost::filesystem::path path)
{
	ImageLoader image(path);

	loadFromMemory(image.getWidth(), image.getHeight(), image.getPixels(), GL_RGBA, GL_BGRA, true, boost::filesystem::canonical(path).string());
}

void Texture::bind(unsigned short texture_level /* = 0 */)
{
	glActiveTexture(GL_TEXTURE0 + texture_level);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Texture::loadFromMemory(unsigned width, unsigned height, GLubyte* pixels, GLint internal_format, GLenum format, bool generate_mipmaps, std::string image_name /* = "" */)
{
	m_width = width;
	m_height = height;

	auto is_power_of_2 = [](unsigned number) -> bool { return !(number & (number - 1)); };
	if (!is_power_of_2(m_width) || !is_power_of_2(m_height))
	{
		if (image_name.empty())
			image_name = "In memory object at 0x" + boost::lexical_cast<std::string>((unsigned)pixels);
		auto dimensions = boost::lexical_cast<std::string>(m_width) + " x " + boost::lexical_cast<std::string>(m_height);
		engine::Config::getInstance().log("Performance warning, image '" + image_name + "' - dimensions " + dimensions + " are not a power of 2", engine::Config::WARNING);
	}

	glGenTextures(1, &m_texture_id);
	m_texture_created = true;

	glBindTexture(GL_TEXTURE_2D, m_texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (generate_mipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);
	
	unbind(); 
}
