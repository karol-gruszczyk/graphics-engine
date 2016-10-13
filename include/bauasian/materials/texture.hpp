#ifndef BAUASIAN_TEXTURE_HPP
#define BAUASIAN_TEXTURE_HPP

#include "texture_interface.hpp"

#include <map>

#include <boost/filesystem/path.hpp>
#include <glm/vec2.hpp>


namespace bauasian
{
	class Texture;
}

class bauasian::Texture final : public TextureInterface
{
public:
	Texture(const glm::uvec2& size, const GLubyte* const pixels, const GLint& internal_format,
		        const GLenum& format, const bool& generate_mipmaps, std::string image_name);
	Texture(const glm::uvec2& size, const GLint& internal_format, const GLenum& format);

	void update(const glm::uvec2& size, const GLint& internal_format, const GLenum& format);
	void save(const boost::filesystem::path& path);

private:
	glm::uvec2 m_size;

};

#endif /* BAUASIAN_TEXTURE_HPP */
