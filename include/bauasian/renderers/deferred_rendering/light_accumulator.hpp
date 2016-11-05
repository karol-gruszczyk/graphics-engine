#ifndef BAUASIAN_LIGHT_RENDERER_HPP
#define BAUASIAN_LIGHT_RENDERER_HPP

#include "bauasian/textures/texture.hpp"
#include "directional_light_pass.hpp"
#include "point_light_pass.hpp"
#include "spot_light_pass.hpp"
#include "ambient_light_pass.hpp"


namespace bauasian
{
	class LightAccumulator;
}

class bauasian::LightAccumulator
{
public:
	LightAccumulator(const glm::uvec2& size, const std::shared_ptr<FrameBufferAttachment>& depth_buffer);

	void setSize(const glm::uvec2& size);
	void render(const Scene3D* scene) const;
	const FrameBuffer& getFrameBuffer() const
	{ return *m_frame_buffer; }

private:
	std::unique_ptr<FrameBuffer> m_frame_buffer;
	std::shared_ptr<Texture> m_accumulation_buffer;

	AmbientLightPass m_ambient_renderer;
	DirectionalLightPass m_directional_light_renderer;
	PointLightPass m_point_light_renderer;
	SpotLightPass m_spot_light_renderer;

};

#endif /* BAUASIAN_LIGHT_RENDERER_HPP */
