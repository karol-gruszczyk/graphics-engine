#include "directional_light_pass.hpp"
#include "bauasian/lights/directional_light.hpp"


using bauasian::DirectionalLightPass;
using bauasian::ShaderProgram;

DirectionalLightPass::DirectionalLightPass()
		: ShaderMixin("deferred_rendering/directional_vs.glsl", "deferred_rendering/directional_fs.glsl")
{}

void DirectionalLightPass::render(const Scene3D* scene) const
{
	m_shader->use();
	for (const auto& light : scene->getDirectionalLights())
	{
		light->bind();
		m_light_volume.render();
	}
}
