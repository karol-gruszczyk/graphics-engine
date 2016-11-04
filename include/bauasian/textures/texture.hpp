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
	Texture(const glm::uvec2& size, const void* pixels, GLint internal_format, GLenum format, bool generate_mipmaps,
			std::string image_name = "", GLenum type = GL_UNSIGNED_BYTE);
	Texture(GLint internal_format, GLenum format, glm::uvec2 size, GLenum type = GL_UNSIGNED_BYTE);

	void save(const boost::filesystem::path& path);

	void setFiltering(GLenum filtering) const;
	void enableDepthComparison() const;
	virtual GLuint getId() const override;
	virtual void setSize(const glm::uvec2& size) override;

};

#endif /* BAUASIAN_TEXTURE_HPP */
