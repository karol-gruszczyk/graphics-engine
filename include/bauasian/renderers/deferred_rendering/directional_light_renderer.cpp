#include "directional_light_renderer.hpp"
#include "bauasian/shaders/buffers/scene_buffer.hpp"
#include "bauasian/shaders/buffers/directional_light_buffer.hpp"


using bauasian::DirectionalLightRenderer;
using bauasian::ShaderProgram;

DirectionalLightRenderer::DirectionalLightRenderer()
		: m_light_volume(std::make_unique<ScreenQuad>())
{
	const auto vs = std::make_unique<Shader>("deferred_rendering/directional_vs.glsl", Shader::VERTEX_SHADER);
	const auto fs = std::make_unique<Shader>("deferred_rendering/directional_fs.glsl", Shader::FRAGMENT_SHADER);
	m_shader = std::make_unique<ShaderProgram>(std::initializer_list<Shader*>{ vs.get(), fs.get() });
	SceneBuffer::getInstance().attachUniformBlock(m_shader.get(), "SceneBuffer");
	DirectionalLightBuffer::getInstance().attachUniformBlock(m_shader.get(), "DirectionalLightBuffer");
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

const ShaderProgram* const DirectionalLightRenderer::getShader() const
{
	return m_shader.get();
}
