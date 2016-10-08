#ifndef BAUASIAN_TEXTURE_HPP
#define BAUASIAN_TEXTURE_HPP

#include <map>

#include <GL/glew.h>
#include <boost/filesystem/path.hpp>


namespace bauasian
{
	class Texture;
}

class bauasian::Texture final
{
public:
	Texture(const unsigned& width, const unsigned& height, const GLubyte* const pixels,
	        const GLint& internal_format, const GLenum& format, const bool& generate_mipmaps,
	        std::string image_name = "");
	Texture(const unsigned& width, const unsigned& height, const GLint& internal_format, const GLenum& format);
	~Texture();

	void update(const unsigned& width, const unsigned& height, const GLint& internal_format, const GLenum& format);
	void save(const boost::filesystem::path& path);
	void bind(unsigned short texture_level = 0) const;
	void unbind() const;
	const GLuint& getTextureId() const;

private:
	GLuint m_texture_id = 0;
	unsigned m_width, m_height;

};

#endif /* BAUASIAN_TEXTURE_HPP */
