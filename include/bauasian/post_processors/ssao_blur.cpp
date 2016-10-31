#include "ssao_blur.hpp"


using bauasian::SSAOBlur;
using bauasian::Texture;

SSAOBlur::SSAOBlur(const glm::uvec2& size, const std::shared_ptr<FrameBufferAttachment>& depth_buffer)
		: ShaderMixin("post_processing/basic_vs.glsl", "post_processing/ssao_blur_fs.glsl")
{
	m_location_pixel_size = m_shader->getUniformLocation("pixel_size");
	m_shader->setUniform(m_location_pixel_size, 1.f / glm::vec2(size));
	m_ssao_texture = std::make_shared<Texture>(GL_RED, GL_RED, size);
	m_frame_buffer = std::make_unique<FrameBuffer>(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
														   { m_ssao_texture },
												   depth_buffer, size);
}

void SSAOBlur::setSize(const glm::uvec2& size) const
{
	m_frame_buffer->setSize(size);
	m_shader->setUniform(m_location_pixel_size, 1.f / glm::vec2(size));
}

void SSAOBlur::process() const
{
	m_frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT);

	m_shader->use();
	m_screen_quad.render();
}

const Texture* const SSAOBlur::getTexture() const
{
	return m_ssao_texture.get();
}
