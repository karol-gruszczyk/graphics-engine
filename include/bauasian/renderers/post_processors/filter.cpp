#include "filter.hpp"


using bauasian::Filter;

Filter::Filter(const boost::filesystem::path& fragment_shader_path, const GLenum& storage)
		: FrameBuffer({ new Texture(storage, GL_RGB) }, new RenderBuffer())
{
	initFrameBuffer();
	Shader fragment_shader(fragment_shader_path, Shader::FRAGMENT_SHADER);
	loadShader(fragment_shader);
}

Filter::Filter(Shader& fragment_shader, const GLenum& storage)
		: FrameBuffer({ new Texture(storage, storage) }, new RenderBuffer())
{
	initFrameBuffer();
	loadShader(fragment_shader);
}

Filter::~Filter()
{
	delete m_screen_quad;
	delete m_shader;
}

void Filter::setSize(const glm::uvec2& size)
{
	FrameBuffer::setSize(size);
	m_color_texture->setSize(size);
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
	m_color_texture = dynamic_cast<Texture*>(getColorAttachments().front());
	m_screen_quad = new ScreenQuad();
}
