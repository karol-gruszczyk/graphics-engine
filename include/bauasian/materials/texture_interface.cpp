#include "texture_interface.hpp"


using bauasian::TextureInterface;

TextureInterface::TextureInterface(const GLenum& texture_target, const GLint& internal_format, const GLenum& format)
		: m_texture_target(texture_target), m_internal_format(internal_format), m_format(format)
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
	glBindTexture(m_texture_target, m_texture_id);
}

void TextureInterface::unbind() const
{
	glBindTexture(m_texture_target, 0);
}
