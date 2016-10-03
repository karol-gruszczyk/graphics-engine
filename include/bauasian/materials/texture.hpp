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
	Texture(unsigned width, unsigned height, GLubyte* pixels, GLint internal_format, GLenum format,
	        bool generate_mipmaps);
	~Texture();

	static Texture* loadFromFile(const boost::filesystem::path& path);
	void loadFromMemory(unsigned width, unsigned height, GLubyte* pixels, GLint internal_format, GLenum format,
	                    bool generate_mipmaps, std::string image_name = "");
	void save(const boost::filesystem::path& path);
	void bind(unsigned short texture_level = 0) const;
	void unbind() const;

private:
	Texture();

	static std::map<std::string, Texture*> s_textures;

	bool m_is_static_instance = false;
	GLuint m_texture_id;
	bool m_texture_created;
	unsigned m_width, m_height;

	static Texture& getStaticInstance();
};

#endif /* BAUASIAN_TEXTURE_HPP */
