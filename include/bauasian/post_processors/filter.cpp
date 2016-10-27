#include "filter.hpp"


using bauasian::Filter;

Filter::Filter(const boost::filesystem::path& fragment_shader_path, const GLenum& storage)
{
	initFrameBuffer(storage);
	Shader fragment_shader(fragment_shader_path, Shader::FRAGMENT_SHADER);
	loadShader(fragment_shader);
}

Filter::Filter(Shader& fragment_shader, const GLenum& storage)
{
	initFrameBuffer(storage);
	loadShader(fragment_shader);
}

Filter::~Filter()
{
	delete m_screen_quad;
	delete m_shader;
	delete m_frame_buffer;
}

void Filter::bindForRendering()
{
	m_frame_buffer->bind();
	m_frame_buffer->clear();
}

void Filter::setSize(const glm::uvec2& size)
{
	m_size = size;
	m_frame_buffer->setSize(size);
	m_color_texture->setSize(size);
}

void Filter::renderToFrameBuffer(const GLuint& fbo_id) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
	glClear(GL_COLOR_BUFFER_BIT);
	m_shader->use();
	m_color_texture->bind(0);
//	glViewport(0, 0, m_size.x, m_size.y);
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

void Filter::initFrameBuffer(const GLenum& storage)
{
	m_color_texture = new Texture(storage, GL_RGB);
	m_frame_buffer = new FrameBuffer({ m_color_texture }, new RenderBuffer());
	m_screen_quad = new ScreenQuad();
}

const GLuint& Filter::getFrameBufferId() const
{
	return m_frame_buffer->getId();
}
