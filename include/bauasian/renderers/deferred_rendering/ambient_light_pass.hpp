#ifndef BAUASIAN_AMBIENT_LIGHT_PASS_HPP
#define BAUASIAN_AMBIENT_LIGHT_PASS_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/primitives/screen_quad.hpp"
#include "bauasian/frame_buffers/frame_buffer.hpp"
#include "bauasian/post_processors/ssao.hpp"


namespace bauasian
{
	class AmbientLightPass;
}

class bauasian::AmbientLightPass : ShaderMixin
{
public:
	AmbientLightPass(const glm::uvec2& size);

	void setSize(const glm::uvec2& size);
	void process(const FrameBuffer* frame_buffer) const;

	void enableSSAO();
	void disableSSAO();

private:
	SSAO m_ssao;
	ScreenQuad m_screen_quad;

	bool m_ssao_enabled = true;
	GLint m_location_ssao_enabled;

};

#endif /* BAUASIAN_AMBIENT_LIGHT_PASS_HPP */
