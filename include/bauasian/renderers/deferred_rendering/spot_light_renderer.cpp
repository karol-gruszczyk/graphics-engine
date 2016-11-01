#include "spot_light_renderer.hpp"
#include "bauasian/shaders/buffers/camera_buffer.hpp"
#include "bauasian/shaders/buffers/matrices_buffer.hpp"
#include "bauasian/shaders/buffers/spot_light_buffer.hpp"


using bauasian::SpotLightRenderer;
using bauasian::ShaderProgram;

SpotLightRenderer::SpotLightRenderer(const glm::uvec2& size)
		: ShaderMixin("deferred_rendering/spot_vs.glsl", "deferred_rendering/spot_fs.glsl")
{
	m_location_spot_light_screen_size = m_shader->getUniformLocation("screen_size");
	CameraBuffer::getInstance().attachUniformBlock(m_shader.get(), "CameraBuffer");
	MatricesBuffer::getInstance().attachUniformBlock(m_shader.get(), "MatricesBuffer");
	SpotLightBuffer::getInstance().attachUniformBlock(m_shader.get(), "SpotLightBuffer");
	setSize(size);
}

void SpotLightRenderer::setSize(const glm::uvec2& size)
{
	m_shader->setUniform(m_location_spot_light_screen_size, size);
}

void SpotLightRenderer::render(const Scene3D* const scene) const
{
	m_shader->use();
	for (const auto& light : scene->getSpotLights())
	{
		SpotLightBuffer::getInstance().setData(light);
		m_light_volume.render();
	}
}
