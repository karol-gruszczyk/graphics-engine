#include "spot_light_renderer.hpp"
#include "bauasian/shaders/buffers/scene_buffer.hpp"
#include "bauasian/shaders/buffers/spot_light_buffer.hpp"


using bauasian::SpotLightRenderer;
using bauasian::ShaderProgram;

SpotLightRenderer::SpotLightRenderer(const glm::uvec2& size)
{
	auto vs = std::make_unique<Shader>("deferred_rendering/spot_vs.glsl", Shader::VERTEX_SHADER);
	auto fs = std::make_unique<Shader>("deferred_rendering/spot_fs.glsl", Shader::FRAGMENT_SHADER);
	m_shader = new ShaderProgram({ vs.get(), fs.get() });
	m_location_spot_light_screen_size = m_shader->getUniformLocation("screen_size");
	m_location_spot_light_projection_view_matrix = m_shader->getUniformLocation("projection_view_matrix");
	SceneBuffer::getInstance().attachUniformBlock(m_shader, "SceneBuffer");
	SpotLightBuffer::getInstance().attachUniformBlock(m_shader, "SpotLightBuffer");
	setSize(size);

	m_light_volume = new ConeVolume();
}

SpotLightRenderer::~SpotLightRenderer()
{
	delete m_shader;
	delete m_light_volume;
}

void SpotLightRenderer::setSize(const glm::uvec2& size)
{
	m_shader->setUniform(m_location_spot_light_screen_size, size);
}

void SpotLightRenderer::render(const Scene3D* const scene) const
{
	m_shader->use();
	m_shader->setUniform(m_location_spot_light_projection_view_matrix,
						 scene->getCamera()->getProjectionViewMatrix());
	for (const auto& light : scene->getSpotLights())
	{
		SpotLightBuffer::getInstance().setData(light);
		m_light_volume->render();
	}
}

const ShaderProgram* const SpotLightRenderer::getShader() const
{
	return m_shader;
}
