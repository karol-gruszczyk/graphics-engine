#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <GL/glew.h>
#include <boost/filesystem/path.hpp>
#include <map>


namespace engine
{
	class Texture;
}

class engine::Texture final
{
public:
	Texture(unsigned width, unsigned height, GLubyte* pixels, GLint internal_format, GLenum format, bool generate_mipmaps);
	~Texture();

	static Texture* loadFromFile(const boost::filesystem::path& path);
	void loadFromMemory(unsigned width, unsigned height, GLubyte* pixels, GLint internal_format, GLenum format, bool generate_mipmaps, std::string image_name = "");
	void bind(unsigned short texture_level = 0) const;
	void unbind() const;

private:
    Texture();
    static std::map<std::string, Texture*> s_textures;
    static Texture& getInstance();

    bool m_static_member = false;
	GLuint m_texture_id;
	bool m_texture_created;
	unsigned m_width, m_height;
};

#endif /* TEXTURE_HPP_ */
