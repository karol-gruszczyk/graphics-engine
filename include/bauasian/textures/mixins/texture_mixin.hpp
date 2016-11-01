#ifndef BAUASIAN_TEXTURE_MIXIN_HPP
#define BAUASIAN_TEXTURE_MIXIN_HPP

#include <GL/glew.h>


namespace bauasian
{
	class TextureMixin;
}

class bauasian::TextureMixin
{
public:
	TextureMixin(const GLenum& texture_target, const GLint& internal_format, const GLenum& format);
	virtual ~TextureMixin();

	void bind(unsigned short texture_level = 0) const;
	void unbind() const;

protected:
	GLuint m_texture_id;
	GLenum m_texture_target;
	GLint m_internal_format;
	GLenum m_format;

};

#endif /* BAUASIAN_TEXTURE_MIXIN_HPP */
