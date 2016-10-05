#ifndef BAUASIAN_TEXTURE_HPP
#define BAUASIAN_TEXTURE_HPP

#include <GL/glew.h>
#include <boost/filesystem/path.hpp>
#include <map>


namespace bauasian
{
	class Texture;
}

class bauasian::Texture final
{
public:
	Texture(const unsigned& width, const unsigned& height, const GLubyte* const pixels,
	        const GLint& internal_format, const GLenum& format, const bool& generate_mipmaps);
	Texture(const unsigned& width, const unsigned& height, const GLint& internal_format, const GLenum& format);
	~Texture();

	void update(const unsigned& width, const unsigned& height, const GLint& internal_format, const GLenum& format);
	static Texture* loadFromFile(const boost::filesystem::path& path);
	void loadFromMemory(const unsigned& width, const unsigned& height, const GLubyte* const pixels,
	                    const GLint& internal_format, const GLenum& format,
	                    const bool& generate_mipmaps, std::string image_name = "");
	void save(const boost::filesystem::path& path);
	void bind(unsigned short texture_level = 0) const;
	void unbind() const;
	const GLuint& getTextureId() const;

private:
	Texture();

	static std::map<std::string, Texture*> s_textures;
	static bool m_anisotropy_ext_supported;

	bool m_is_static_instance = false;
	GLuint m_texture_id = 0;
private:
	unsigned m_width, m_height;

	static Texture& getStaticInstance();
};

#endif /* BAUASIAN_TEXTURE_HPP */
