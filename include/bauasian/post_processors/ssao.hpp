#ifndef BAUASIAN_SSAO_HPP
#define BAUASIAN_SSAO_HPP

#include "bauasian/mixins/shader_mixin.hpp"
#include "bauasian/renderers/frame_buffer.hpp"
#include "bauasian/materials/texture.hpp"
#include "bauasian/primitives/screen_quad.hpp"


namespace bauasian
{
	class SSAO;
}

class bauasian::SSAO : public ShaderMixin
{
public:
	SSAO(const glm::uvec2& size);

	void setSize(const glm::uvec2& size);
	void process(const FrameBuffer* const frame_buffer) const;

private:
	ScreenQuad m_screen_quad;
	std::unique_ptr<Texture> m_noise_texture;
	std::shared_ptr<Texture> m_ssao_texture;
	std::unique_ptr<FrameBuffer> m_frame_buffer;

};

#endif /* BAUASIAN_SSAO_HPP */
