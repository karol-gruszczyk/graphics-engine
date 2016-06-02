#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>
#include <boost/filesystem/path.hpp>


namespace engine
{
	class Texture;
}

class engine::Texture final
{
public:
	Texture(boost::filesystem::path path);
	Texture(unsigned width, unsigned height, GLubyte* pixels, GLint internal_format, GLenum format, bool generate_mipmaps);
	~Texture();

	void loadFromFile(boost::filesystem::path path);
	void loadFromMemory(unsigned width, unsigned height, GLubyte* pixels, GLint internal_format, GLenum format, bool generate_mipmaps, std::string image_name = "");
	void bind(unsigned short texture_level = 0);
	void unbind();
private:
	GLuint m_texture_id;
	bool m_texture_created;
	unsigned m_width, m_height;
};

#endif /* TEXTURE_H_ */
