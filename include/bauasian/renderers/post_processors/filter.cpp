#include "filter.hpp"


using bauasian::Filter;

Filter::Filter(const boost::filesystem::path& fragment_shader_path)
		: FrameBuffer(glm::uvec2(1, 1), {})
{
	initFrameBuffer();
	Shader fragment_shader(fragment_shader_path, Shader::FRAGMENT_SHADER);
	loadShader(fragment_shader);
}

Filter::Filter(Shader& fragment_shader)
		: FrameBuffer(glm::uvec2(1, 1), {})
{
	initFrameBuffer();
	loadShader(fragment_shader);
}

Filter::~Filter()
{
	glDeleteRenderbuffers(1, &m_rbo_id);
	delete m_color_texture;
	delete m_screen_quad;
	delete m_shader;
}

void Filter::setContextSize(const unsigned& width, const unsigned& height) const
{
	m_color_texture->setSize({ width, height });

	glNamedRenderbufferStorage(m_rbo_id, GL_DEPTH24_STENCIL8, width, height);
}

void Filter::renderToScreen() const
{
	m_shader->use();
	m_color_texture->bind(0);
	m_screen_quad->render();
}

void Filter::loadShader(Shader& fragment_shader)
{
	if (m_shader)
		delete m_shader;
	Shader* vertex_shader = new Shader("post_processing/basic_vs.glsl", Shader::VERTEX_SHADER);
	m_shader = new ShaderProgram({ vertex_shader, &fragment_shader });
	delete vertex_shader;
}

void Filter::initFrameBuffer()
{
	unsigned size = 1;
	m_color_texture = new Texture({ size, size }, GL_RGB, GL_RGB);

	glGenRenderbuffers(1, &m_rbo_id);
	glNamedRenderbufferStorageEXT(m_rbo_id, GL_DEPTH24_STENCIL8, size, size);

	glNamedFramebufferTexture2DEXT(m_fbo_id, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture->getTextureId(), 0);
	glNamedFramebufferRenderbuffer(m_fbo_id, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo_id);
	assert(glCheckNamedFramebufferStatus(m_fbo_id, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	m_screen_quad = new ScreenQuad();
}
