#ifndef BAUASIAN_AMBIENT_RENDERER_HPP
#define BAUASIAN_AMBIENT_RENDERER_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/primitives/screen_quad.hpp"
#include "bauasian/renderers/frame_buffer.hpp"
#include "bauasian/post_processors/ssao.hpp"


namespace bauasian
{
	class AmbientLightRenderer;
}

class bauasian::AmbientLightRenderer : ShaderMixin
{
public:
	AmbientLightRenderer(const glm::uvec2& size);

	void setSize(const glm::uvec2& size);
	void process(const FrameBuffer* const frame_buffer) const;

private:
	SSAO m_ssao;
	ScreenQuad m_screen_quad;

};

#endif /* BAUASIAN_AMBIENT_RENDERER_HPP */
