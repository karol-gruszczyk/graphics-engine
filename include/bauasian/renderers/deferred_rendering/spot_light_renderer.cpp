#include "spot_light_renderer.hpp"
#include "bauasian/uniform_buffers/matrices_buffer.hpp"
#include "bauasian/uniform_buffers/spot_light_buffer.hpp"


using bauasian::SpotLightRenderer;
using bauasian::ShaderProgram;

SpotLightRenderer::SpotLightRenderer(const glm::uvec2& size)
		: ShaderMixin("deferred_rendering/spot_vs.glsl", "deferred_rendering/spot_fs.glsl")
{
	m_location_spot_light_screen_size = m_shader->getUniformLocation("screen_size");
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
		SpotLightBuffer::getInstance().setModelMatrix(light->getModelMatrix());
		SpotLightBuffer::getInstance().setDiffuseColor(light->getDiffuseColor());
		SpotLightBuffer::getInstance().setSpecularColor(light->getSpecularColor());
		SpotLightBuffer::getInstance().setPosition(light->getPosition());
		SpotLightBuffer::getInstance().setDirection(light->getDirection());
		SpotLightBuffer::getInstance().setAttenuation(light->getAttenuation());
		SpotLightBuffer::getInstance().setInnerAngle(light->getInnerAngle());
		SpotLightBuffer::getInstance().setOuterAngle(light->getOuterAngle());
		SpotLightBuffer::getInstance().bind();
		m_light_volume.render();
	}
}
