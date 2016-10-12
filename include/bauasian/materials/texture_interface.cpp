#include "texture_interface.hpp"


using bauasian::TextureInterface;

TextureInterface::TextureInterface()
{
	glGenTextures(1, &m_texture_id);
}

TextureInterface::~TextureInterface()
{
	glDeleteTextures(1, &m_texture_id);
}

const GLuint& TextureInterface::getTextureId() const
{
	return m_texture_id;
}

void TextureInterface::bind(unsigned short texture_level) const
{
	glActiveTexture(GL_TEXTURE0 + texture_level);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void TextureInterface::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
