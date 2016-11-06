#ifndef BAUASIAN_FILTER_HPP
#define BAUASIAN_FILTER_HPP

#include "post_processor.hpp"
#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/frame_buffers/frame_buffer.hpp"
#include "bauasian/textures/texture.hpp"
#include "bauasian/primitives/screen_quad.hpp"


namespace bauasian
{
	class Filter;
}

class bauasian::Filter : public PostProcessor, public ShaderMixin
{
public:
	Filter(const glm::uvec2& size, const boost::filesystem::path& vertex_shader_path,
		   const boost::filesystem::path& fragment_shader_path, GLenum storage);
	Filter(const glm::uvec2& size, const boost::filesystem::path& fragment_shader_path, GLenum storage);
	virtual ~Filter() {}

	virtual void setSize(const glm::uvec2& size) override;
	virtual void process(unsigned short out_binding = POST_PROCESSING_COLOR_TEXTURE) const override;
	virtual void processToScreen() const override;
	virtual void process(const Texture* texture) const override;
	virtual const Texture* getTexture() const override;

protected:
	std::unique_ptr<FrameBuffer> m_frame_buffer;
	std::shared_ptr<Texture> m_color_texture;

private:
	ScreenQuad m_screen_quad;

};

#endif /* BAUASIAN_FILTER_HPP */
