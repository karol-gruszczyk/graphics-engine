#include "point_light_renderer.hpp"
#include "bauasian/shaders/buffers/scene_buffer.hpp"
#include "bauasian/shaders/buffers/point_light_buffer.hpp"


using bauasian::PointLightRenderer;
using bauasian::ShaderProgram;

PointLightRenderer::PointLightRenderer(const glm::uvec2& size)
		: m_light_volume(std::make_unique<SphereVolume>())
{
	const auto vs = std::make_unique<Shader>("deferred_rendering/point_vs.glsl", Shader::VERTEX_SHADER);
	const auto fs = std::make_unique<Shader>("deferred_rendering/point_fs.glsl", Shader::FRAGMENT_SHADER);
	m_shader = std::make_unique<ShaderProgram>(std::initializer_list<Shader*>{ vs.get(), fs.get() });
	m_location_point_light_projection_view_matrix = m_shader->getUniformLocation("projection_view_matrix");
	m_location_point_light_screen_size = m_shader->getUniformLocation("screen_size");
	SceneBuffer::getInstance().attachUniformBlock(m_shader.get(), "SceneBuffer");
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

const ShaderProgram* const PointLightRenderer::getShader() const
{
	return m_shader.get();
}
