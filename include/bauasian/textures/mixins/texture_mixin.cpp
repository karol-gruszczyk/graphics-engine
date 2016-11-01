#include "texture_mixin.hpp"


using bauasian::TextureMixin;

TextureMixin::TextureMixin(const GLenum& texture_target, const GLint& internal_format, const GLenum& format)
		: m_texture_target(texture_target), m_internal_format(internal_format), m_format(format)
{
	glGenTextures(1, &m_texture_id);
}

TextureMixin::~TextureMixin()
{
	glDeleteTextures(1, &m_texture_id);
}

void TextureMixin::bind(unsigned short texture_level) const
{
	glActiveTexture(GL_TEXTURE0 + texture_level);
	glBindTexture(m_texture_target, m_texture_id);
}

void TextureMixin::unbind() const
{
	glBindTexture(m_texture_target, 0);
}
