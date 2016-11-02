#include "point_light_pass.hpp"
#include "bauasian/uniform_buffers/matrices_buffer.hpp"


using bauasian::PointLightPass;
using bauasian::ShaderProgram;

PointLightPass::PointLightPass(const glm::uvec2& size)
		: ShaderMixin("deferred_rendering/point_vs.glsl", "deferred_rendering/point_fs.glsl")
{
	m_location_point_light_screen_size = m_shader->getUniformLocation("screen_size");
	setSize(size);
}

void PointLightPass::setSize(const glm::uvec2& size)
{
	m_shader->setUniform(m_location_point_light_screen_size, size);
}

void PointLightPass::render(const Scene3D* const scene) const
{
	m_shader->use();
	for (const auto& light : scene->getPointLights())
	{
		light->bind();
		m_light_volume.render();
	}
}
