#ifndef BAUASIAN_SSAO_BLUR_HPP
#define BAUASIAN_SSAO_BLUR_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/renderers/frame_buffer.hpp"
#include "bauasian/materials/texture.hpp"
#include "bauasian/primitives/screen_quad.hpp"


namespace bauasian
{
	class SSAOBlur;
}

class bauasian::SSAOBlur : public ShaderMixin
{
public:
	SSAOBlur(const glm::uvec2& size, const std::shared_ptr<FrameBufferAttachment>& depth_buffer);

	void setSize(const glm::uvec2& size) const;
	void process() const;
	const Texture* const getTexture() const;

private:
	std::shared_ptr<Texture> m_ssao_texture;
	std::unique_ptr<FrameBuffer> m_frame_buffer;
	ScreenQuad m_screen_quad;

	GLint m_location_pixel_size;

};

#endif /* BAUASIAN_SSAO_BLUR_HPP */
