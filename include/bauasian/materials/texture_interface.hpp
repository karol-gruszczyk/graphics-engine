#ifndef BAUASIAN_TEXTURE_INTERFACE_HPP
#define BAUASIAN_TEXTURE_INTERFACE_HPP

#include <GL/glew.h>


namespace bauasian
{
	class TextureInterface;
}

class bauasian::TextureInterface
{
public:
	TextureInterface(const GLenum& texture_target);
	~TextureInterface();

	const GLuint& getTextureId() const;
	void bind(unsigned short texture_level = 0) const;
	void unbind() const;

protected:
	GLuint m_texture_id;
	GLenum m_texture_target;

};

#endif /* BAUASIAN_TEXTURE_INTERFACE_HPP */
