#include "filter.hpp"


using bauasian::Filter;
using bauasian::Texture;

Filter::Filter(const glm::uvec2& size, const boost::filesystem::path& vertex_shader_path,
			   const boost::filesystem::path& fragment_shader_path, GLenum storage)
		: ShaderMixin(vertex_shader_path, fragment_shader_path)
{
	m_color_texture = std::make_shared<Texture>(storage, GL_RGB, size);
	m_frame_buffer = std::make_unique<FrameBuffer>(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
														   { m_color_texture },
												   std::make_shared<RenderBuffer>(size), size);
}

Filter::Filter(const glm::uvec2& size, const boost::filesystem::path& fragment_shader_path, GLenum storage)
		: Filter(size, "post_processing/basic_vs.glsl", fragment_shader_path, storage)
{}

void Filter::setSize(const glm::uvec2& size)
{
	m_frame_buffer->setSize(size);
}

void Filter::process(unsigned short out_binding) const
{
	m_frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader->use();
	m_screen_quad.render();

	m_color_texture->bind(out_binding);
}

void Filter::processToScreen() const
{
	m_frame_buffer->unbind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader->use();
	m_screen_quad.render();
}

void Filter::process(const Texture* texture) const
{
	texture->bind(POST_PROCESSING_COLOR_TEXTURE);
	m_frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader->use();
	m_screen_quad.render();
}

const Texture* Filter::getTexture() const
{
	return m_color_texture.get();
}
