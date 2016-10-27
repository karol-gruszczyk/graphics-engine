#ifndef BAUASIAN_LIGHT_RENDERER_HPP
#define BAUASIAN_LIGHT_RENDERER_HPP

#include "bauasian/renderers/frame_buffer.hpp"
#include "bauasian/materials/texture.hpp"
#include "directional_light_renderer.hpp"
#include "point_light_renderer.hpp"


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

private:
	std::unique_ptr<FrameBuffer> m_frame_buffer = nullptr;
	std::shared_ptr<Texture> m_accumulation_buffer;

	DirectionalLightRenderer m_directional_light_renderer;
	PointLightRenderer m_point_light_renderer;

	void initializeTextureLocations(const ShaderProgram* const shader) const;

};


#endif /* BAUASIAN_LIGHT_RENDERER_HPP */
