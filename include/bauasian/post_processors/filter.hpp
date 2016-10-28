#ifndef BAUASIAN_FILTER_HPP
#define BAUASIAN_FILTER_HPP

#include "post_processor.hpp"
#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/renderers/frame_buffer.hpp"
#include "bauasian/materials/texture.hpp"
#include "bauasian/primitives/screen_quad.hpp"


namespace bauasian
{
	class Filter;
}

class bauasian::Filter : public PostProcessor, public ShaderMixin
{
public:
	Filter(const boost::filesystem::path& fragment_shader_path, const GLenum& storage = GL_RGBA);
	virtual ~Filter() {}

	virtual void setSize(const glm::uvec2& size) override;
	virtual void process(const Texture* const texture, bool to_screen = true) const override;
	virtual const Texture* const getTexture() const override;

protected:
	std::unique_ptr<FrameBuffer> m_frame_buffer;
	std::shared_ptr<Texture> m_color_texture;

private:
	std::unique_ptr<ScreenQuad> m_screen_quad;

};

#endif /* BAUASIAN_FILTER_HPP */
