#include "ambient_light_pass.hpp"
#include "bauasian/glsl/bindings.glsl"


using bauasian::AmbientLightPass;

AmbientLightPass::AmbientLightPass(const glm::uvec2& size)
		: ShaderMixin("post_processing/basic_vs.glsl", "deferred_rendering/ambient_fs.glsl"), m_ssao(size)
{
	m_location_ssao_enabled = m_shader->getUniformLocation("ssao_enabled");
	enableSSAO();
}

void AmbientLightPass::setSize(const glm::uvec2& size)
{
	m_ssao.setSize(size);
}

void AmbientLightPass::process(const FrameBuffer* frame_buffer) const
{
	if (m_ssao_enabled)
		m_ssao.process();

	frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT);

	m_shader->use();
	m_screen_quad.render();
}

void AmbientLightPass::enableSSAO()
{
	m_ssao_enabled = true;
	m_shader->setUniform(m_location_ssao_enabled, true);
}

void AmbientLightPass::disableSSAO()
{
	m_ssao_enabled = false;
	m_shader->setUniform(m_location_ssao_enabled, false);
}
