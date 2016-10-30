#ifndef BAUASIAN_LIGHT_RENDERER_HPP
#define BAUASIAN_LIGHT_RENDERER_HPP

#include "bauasian/renderers/frame_buffer.hpp"
#include "bauasian/materials/texture.hpp"
#include "directional_light_renderer.hpp"
#include "point_light_renderer.hpp"
#include "spot_light_renderer.hpp"
#include "bauasian/post_processors/ssao.hpp"


namespace bauasian
{
	class LightAccumulator;
}

class bauasian::LightAccumulator
{
public:
	LightAccumulator(const glm::uvec2& size, const std::shared_ptr<FrameBufferAttachment>& depth_buffer);

	void setSize(const glm::uvec2& size);
	void render(const Scene3D* const scene) const;
	const Texture* const getTexture() const;
	const FrameBuffer& getFrameBuffer() const;

private:
	std::unique_ptr<FrameBuffer> m_frame_buffer;
	std::shared_ptr<Texture> m_accumulation_buffer;

	SSAO m_ssao;
	DirectionalLightRenderer m_directional_light_renderer;
	PointLightRenderer m_point_light_renderer;
	SpotLightRenderer m_spot_light_renderer;

};

#endif /* BAUASIAN_LIGHT_RENDERER_HPP */
