#include "filter.hpp"
#include "bauasian/bauasian.hpp"


using bauasian::Filter;

Filter::Filter(const boost::filesystem::path& fragment_shader_path)
{
	glGenFramebuffers(1, &m_fbo_id);

	unsigned size = 1;
	m_color_texture = new Texture(size, size, GL_RGB, GL_RGB);

	glGenRenderbuffers(1, &m_rbo_id);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size, size);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture->getTextureId(), 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo_id);
	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	unbind();

	m_screen_quad = new ScreenQuad();

	Shader* vertex_shader = new Shader("post_processing/basic_vs.glsl", Shader::VERTEX_SHADER);
	Shader* fragment_shader = new Shader("post_processing/" / fragment_shader_path, Shader::FRAGMENT_SHADER);
	m_shader = new ShaderProgram({ vertex_shader, fragment_shader });
	delete vertex_shader;
	delete fragment_shader;
}

Filter::~Filter()
{
	glDeleteFramebuffers(1, &m_fbo_id);
	glDeleteRenderbuffers(1, &m_rbo_id);
	delete m_color_texture;
	delete m_screen_quad;
	delete m_shader;
}

void Filter::setContextSize(const unsigned& width, const unsigned& height) const
{
	m_color_texture->update(width, height, GL_RGB, GL_RGB);

	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Filter::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_id);
}

void Filter::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Filter::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Filter::renderToScreen() const
{
	m_shader->bind();
	m_color_texture->bind(0);
	m_screen_quad->render();
}
