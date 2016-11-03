#ifndef BAUASIAN_TEXTURE_HPP
#define BAUASIAN_TEXTURE_HPP

#include "mixins/texture_mixin.hpp"
#include "bauasian/frame_buffers/frame_buffer_attachment.hpp"

#include <map>

#include <boost/filesystem/path.hpp>
#include <glm/vec2.hpp>


namespace bauasian
{
	class Texture;
}

class bauasian::Texture final : public TextureMixin, public FrameBufferAttachment
{
public:
	Texture(const glm::uvec2& size, const void* const pixels, const GLint& internal_format,
	        const GLenum& format, const bool& generate_mipmaps, std::string image_name = "",
			const GLenum& type = GL_UNSIGNED_BYTE);
	Texture(const GLint& internal_format, const GLenum& format, const glm::uvec2& size,
			const GLenum& type = GL_UNSIGNED_BYTE);

	void save(const boost::filesystem::path& path);

	void setFiltering(const GLenum& filtering) const;
	void enableDepthComparison() const;
	virtual const GLuint& getId() const override;
	virtual void setSize(const glm::uvec2& size) override;

};

#endif /* BAUASIAN_TEXTURE_HPP */
