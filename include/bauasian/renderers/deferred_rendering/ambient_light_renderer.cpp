#include "ambient_light_renderer.hpp"
#include "bauasian/glsl/bindings.glsl"


using bauasian::AmbientLightRenderer;

AmbientLightRenderer::AmbientLightRenderer(const glm::uvec2& size)
		: ShaderMixin("post_processing/basic_vs.glsl", "deferred_rendering/ambient_fs.glsl"), m_ssao(size)
{}

void AmbientLightRenderer::setSize(const glm::uvec2& size)
{
	m_ssao.setSize(size);
}

void AmbientLightRenderer::process(const FrameBuffer* const frame_buffer) const
{
	frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT);
//	m_ssao.process();
}
