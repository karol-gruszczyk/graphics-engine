#include "filter.hpp"


using bauasian::Filter;
using bauasian::Texture;

Filter::Filter(const glm::uvec2& size, const boost::filesystem::path& fragment_shader_path, const GLenum& storage)
		: ShaderMixin("post_processing/basic_vs.glsl", fragment_shader_path),
		  m_screen_quad(std::make_unique<ScreenQuad>())
{
	m_color_texture = std::make_shared<Texture>(storage, GL_RGB, size);
	m_frame_buffer = std::make_unique<FrameBuffer>(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
														   { m_color_texture },
												   std::make_shared<RenderBuffer>(size), size);
}

void Filter::setSize(const glm::uvec2& size)
{
	m_frame_buffer->setSize(size);
}

void Filter::process(const Texture* const texture) const
{
	m_frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader->use();
	texture->bind();
	m_screen_quad->render();
}

void Filter::processToScreen(const Texture* const texture) const
{
	m_frame_buffer->unbind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader->use();
	texture->bind();
	m_screen_quad->render();
}

const Texture* const Filter::getTexture() const
{
	return m_color_texture.get();
}
