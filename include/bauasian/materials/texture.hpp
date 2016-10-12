#ifndef BAUASIAN_TEXTURE_HPP
#define BAUASIAN_TEXTURE_HPP

#include "texture_interface.hpp"

#include <map>

#include <boost/filesystem/path.hpp>


namespace bauasian
{
	class Texture;
}

class bauasian::Texture final : public TextureInterface
{
public:
	Texture(const unsigned& width, const unsigned& height, const GLubyte* const pixels,
	        const GLint& internal_format, const GLenum& format, const bool& generate_mipmaps,
	        std::string image_name = "");
	Texture(const unsigned& width, const unsigned& height, const GLint& internal_format, const GLenum& format);

	void update(const unsigned& width, const unsigned& height, const GLint& internal_format, const GLenum& format);
	void save(const boost::filesystem::path& path);

private:
	unsigned m_width, m_height;

};

#endif /* BAUASIAN_TEXTURE_HPP */
