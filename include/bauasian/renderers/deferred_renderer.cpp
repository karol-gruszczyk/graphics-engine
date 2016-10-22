#include "deferred_renderer.hpp"
#include "bauasian/shaders/buffers/model_matrices_buffer.hpp"
#include "bauasian/shaders/buffers/scene_buffer.hpp"


#define ALBEDO_BUFFER 0
#define SPECULAR_BUFFER 1
#define NORMAL_BUFFER 2
#define POSITION_BUFFER 3

using bauasian::DeferredRenderer;

DeferredRenderer::DeferredRenderer(const glm::uvec2 size)
		: SizeInterface(size)
{
	m_albedo_buffer = new Texture(GL_RGB, GL_RGB, size);
	m_specular_buffer = new Texture(GL_RGB, GL_RGBA, size);
	m_normal_buffer = new Texture(GL_RGB16F, GL_RGB, size);
	m_position_buffer = new Texture(GL_RGB16F, GL_RGB, size);
	m_frame_buffer = new FrameBuffer({ m_albedo_buffer, m_specular_buffer, m_normal_buffer, m_position_buffer },
									 new RenderBuffer(), size);
	Shader* vs = new Shader("deferred_rendering/gbuffer_vs.glsl", Shader::VERTEX_SHADER);
	Shader* fs = new Shader("deferred_rendering/gbuffer_fs.glsl", Shader::FRAGMENT_SHADER);
	m_geometry_shader = new ShaderProgram({ vs, fs });
	delete vs;
	delete fs;

	Material::setShaderLocations(m_geometry_shader);
	ModelMatricesBuffer::getInstance().attachUniformBlock(m_geometry_shader, "ModelMatrices");
	SceneBuffer::getInstance().attachUniformBlock(m_geometry_shader, "SceneBuffer");

	vs = new Shader("deferred_rendering/lighting_vs.glsl", Shader::VERTEX_SHADER);
	fs = new Shader("deferred_rendering/directional_fs.glsl", Shader::FRAGMENT_SHADER);
	m_dir_light_shader = new ShaderProgram({ vs, fs });
	delete vs;
	delete fs;
	initUniformLocations(m_dir_light_shader);

	m_screen_quad = new ScreenQuad();
}

DeferredRenderer::~DeferredRenderer()
{
	delete m_frame_buffer;
	delete m_geometry_shader;
	delete m_dir_light_shader;
	delete m_screen_quad;
}

void DeferredRenderer::setSize(const glm::uvec2& size)
{
	SizeInterface::setSize(size);
	m_frame_buffer->setSize(size);
}

void DeferredRenderer::render(Scene3D* scene) const
{
	m_frame_buffer->bind();
	m_frame_buffer->clear();
	m_geometry_shader->use();
	scene->render();

	m_frame_buffer->unbind();
	m_dir_light_shader->use();
	m_albedo_buffer->bind(ALBEDO_BUFFER);
	m_specular_buffer->bind(SPECULAR_BUFFER);
	m_normal_buffer->bind(NORMAL_BUFFER);
	m_position_buffer->bind(POSITION_BUFFER);
	m_screen_quad->render();
}

void DeferredRenderer::initUniformLocations(ShaderProgram* shader) const
{
	shader->setUniform(shader->getUniformLocation("albedo_buffer"), ALBEDO_BUFFER);
	shader->setUniform(shader->getUniformLocation("specular_buffer"), SPECULAR_BUFFER);
	shader->setUniform(shader->getUniformLocation("normal_buffer"), NORMAL_BUFFER);
	shader->setUniform(shader->getUniformLocation("position_buffer"), POSITION_BUFFER);
}
