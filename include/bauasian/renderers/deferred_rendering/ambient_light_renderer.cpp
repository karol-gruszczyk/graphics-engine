#include "ambient_light_renderer.hpp"
#include "bauasian/glsl/bindings.glsl"


using bauasian::AmbientLightRenderer;

AmbientLightRenderer::AmbientLightRenderer(const glm::uvec2& size,
										   const std::shared_ptr<FrameBufferAttachment>& depth_buffer)
		: ShaderMixin("post_processing/basic_vs.glsl", "deferred_rendering/ambient_fs.glsl"), m_ssao(size, depth_buffer)
{}

void AmbientLightRenderer::setSize(const glm::uvec2& size)
{
	m_ssao.setSize(size);
}

void AmbientLightRenderer::process(const FrameBuffer* const frame_buffer) const
{
	m_ssao.process();

	frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT);

	m_shader->use();
	m_ssao.getTexture()->bind(DEFERRED_SSAO_BINDING);
	m_screen_quad.render();
}
