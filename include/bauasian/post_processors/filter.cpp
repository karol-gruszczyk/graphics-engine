#include "filter.hpp"


using bauasian::Filter;
using bauasian::Texture;

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

void Filter::setSize(const glm::uvec2& size)
{
	m_size = size;
	m_frame_buffer->setSize(size);
	m_color_texture->setSize(size);
}

void Filter::process(const Texture* const texture, bool to_screen) const
{
	if (to_screen)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	else
		m_frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader->use();
	texture->bind();
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
	m_color_texture = std::make_shared<Texture>(storage, GL_RGB);
	m_frame_buffer = new FrameBuffer(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
											 { m_color_texture },
			std::make_shared<RenderBuffer>());
	m_screen_quad = new ScreenQuad();
}

const Texture* const Filter::getTexture() const
{
	return m_color_texture.get();
}
