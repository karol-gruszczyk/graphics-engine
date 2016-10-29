#include "directional_light_renderer.hpp"
#include "bauasian/shaders/buffers/camera_buffer.hpp"
#include "bauasian/shaders/buffers/directional_light_buffer.hpp"


using bauasian::DirectionalLightRenderer;
using bauasian::ShaderProgram;

DirectionalLightRenderer::DirectionalLightRenderer()
		: ShaderMixin("deferred_rendering/directional_vs.glsl", "deferred_rendering/directional_fs.glsl"),
		  m_light_volume(std::make_unique<ScreenQuad>())
{
	CameraBuffer::getInstance().attachUniformBlock(m_shader.get(), "CameraBuffer");
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
