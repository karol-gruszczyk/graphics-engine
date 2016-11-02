#include "directional_light_renderer.hpp"
#include "bauasian/buffers/directional_light_buffer.hpp"


using bauasian::DirectionalLightRenderer;
using bauasian::ShaderProgram;

DirectionalLightRenderer::DirectionalLightRenderer()
		: ShaderMixin("deferred_rendering/directional_vs.glsl", "deferred_rendering/directional_fs.glsl")
{
	DirectionalLightBuffer::getInstance().attachUniformBlock(m_shader.get(), "DirectionalLightBuffer");
}

void DirectionalLightRenderer::render(const Scene3D* const scene) const
{
	m_shader->use();
	for (const auto& light : scene->getDirectionalLights())
	{
		DirectionalLightBuffer::getInstance().setData(light);
		m_light_volume.render();
	}
}
