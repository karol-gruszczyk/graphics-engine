#include "directional_light_renderer.hpp"
#include "bauasian/uniform_buffers/directional_light_buffer.hpp"


using bauasian::DirectionalLightRenderer;
using bauasian::ShaderProgram;

DirectionalLightRenderer::DirectionalLightRenderer()
		: ShaderMixin("deferred_rendering/directional_vs.glsl", "deferred_rendering/directional_fs.glsl")
{}

void DirectionalLightRenderer::render(const Scene3D* const scene) const
{
	m_shader->use();
	for (const auto& light : scene->getDirectionalLights())
	{
		light->bind();
		m_light_volume.render();
	}
}
