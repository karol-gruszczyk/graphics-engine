#include "directional_light_renderer.hpp"
#include "bauasian/shaders/buffers/scene_buffer.hpp"
#include "bauasian/shaders/buffers/directional_light_buffer.hpp"


using bauasian::DirectionalLightRenderer;

DirectionalLightRenderer::DirectionalLightRenderer()
{
	auto vs = std::make_unique<Shader>("deferred_rendering/directional_vs.glsl", Shader::VERTEX_SHADER);
	auto fs = std::make_unique<Shader>("deferred_rendering/directional_fs.glsl", Shader::FRAGMENT_SHADER);
	m_shader = new ShaderProgram({ vs.get(), fs.get() });
	SceneBuffer::getInstance().attachUniformBlock(m_shader, "SceneBuffer");
	DirectionalLightBuffer::getInstance().attachUniformBlock(m_shader, "DirectionalLightBuffer");

	m_light_volume = new ScreenQuad();
}

DirectionalLightRenderer::~DirectionalLightRenderer()
{
	delete m_shader;
	delete m_light_volume;
}

void DirectionalLightRenderer::render(const Scene3D* const scene) const
{
	m_shader->use();
	for (const auto& light : scene->getDirectionalLights())
	{
		DirectionalLightBuffer::getInstance().setData(light);
		m_light_volume->render();
	}
}
