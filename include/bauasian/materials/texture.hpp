#ifndef BAUASIAN_TEXTURE_HPP
#define BAUASIAN_TEXTURE_HPP

#include "texture_interface.hpp"
#include "bauasian/renderers/frame_buffer_attachment.hpp"

#include <map>

#include <boost/filesystem/path.hpp>
#include <glm/vec2.hpp>


namespace bauasian
{
	class Texture;
}

class bauasian::Texture final : public TextureInterface, public FrameBufferAttachment
{
public:
	Texture(const glm::uvec2& size, const GLubyte* const pixels, const GLint& internal_format,
	        const GLenum& format, const bool& generate_mipmaps, std::string image_name);
	Texture(const GLint& internal_format, const GLenum& format, const glm::uvec2& size = { 1, 1 });

	void save(const boost::filesystem::path& path);

	virtual const GLuint& getId() const override;
	virtual void setSize(const glm::uvec2& size) override;

};

#endif /* BAUASIAN_TEXTURE_HPP */
