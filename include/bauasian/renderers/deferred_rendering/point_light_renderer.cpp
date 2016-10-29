#include "point_light_renderer.hpp"
#include "bauasian/shaders/buffers/camera_buffer.hpp"
#include "bauasian/shaders/buffers/point_light_buffer.hpp"


using bauasian::PointLightRenderer;
using bauasian::ShaderProgram;

PointLightRenderer::PointLightRenderer(const glm::uvec2& size)
		: ShaderMixin("deferred_rendering/point_vs.glsl", "deferred_rendering/point_fs.glsl"),
		  m_light_volume(std::make_unique<SphereVolume>())
{
	m_location_point_light_projection_view_matrix = m_shader->getUniformLocation("projection_view_matrix");
	m_location_point_light_screen_size = m_shader->getUniformLocation("screen_size");
	CameraBuffer::getInstance().attachUniformBlock(m_shader.get(), "CameraBuffer");
	PointLightBuffer::getInstance().attachUniformBlock(m_shader.get(), "PointLightBuffer");
	setSize(size);
}

void PointLightRenderer::setSize(const glm::uvec2& size)
{
	m_shader->setUniform(m_location_point_light_screen_size, size);
}

void PointLightRenderer::render(const Scene3D* const scene) const
{
	m_shader->use();
	m_shader->setUniform(m_location_point_light_projection_view_matrix,
						 scene->getCamera()->getProjectionViewMatrix());
	for (const auto& light : scene->getPointLights())
	{
		PointLightBuffer::getInstance().setData(light);
		m_light_volume->render();
	}
}
