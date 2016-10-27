#include "geometry_renderer.hpp"
#include "bauasian/shaders/buffers/model_matrices_buffer.hpp"
#include "bauasian/shaders/buffers/scene_buffer.hpp"


using bauasian::GeometryRenderer;

GeometryRenderer::GeometryRenderer(const glm::uvec2& size)
		: m_size(size)
{
	m_albedo_buffer = std::make_shared<Texture>(GL_RGB, GL_RGB, size);
	m_specular_buffer = std::make_shared<Texture>(GL_RGBA, GL_RGBA, size);
	m_normal_buffer = std::make_shared<Texture>(GL_RGB16F, GL_RGB, size);
	m_position_buffer = std::make_shared<Texture>(GL_RGB16F, GL_RGB, size);
	m_frame_buffer = new FrameBuffer(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
											 { m_albedo_buffer, m_specular_buffer, m_normal_buffer, m_position_buffer },
									 std::make_shared<RenderBuffer>(), size);

	auto vs = std::make_unique<Shader>("deferred_rendering/gbuffer_vs.glsl", Shader::VERTEX_SHADER);
	auto fs = std::make_unique<Shader>("deferred_rendering/gbuffer_fs.glsl", Shader::FRAGMENT_SHADER);
	m_shader = new ShaderProgram({ vs.get(), fs.get() });

	Material::setShaderLocations(m_shader);
	ModelMatricesBuffer::getInstance().attachUniformBlock(m_shader, "ModelMatrices");
	SceneBuffer::getInstance().attachUniformBlock(m_shader, "SceneBuffer");
}

GeometryRenderer::~GeometryRenderer()
{
	delete m_frame_buffer;
	delete m_shader;
}

void GeometryRenderer::setSize(const glm::uvec2& size)
{
	m_size = size;
	m_frame_buffer->setSize(m_size);
}

void GeometryRenderer::render(const bauasian::Scene3D* const scene)
{
	m_frame_buffer->bind();
	m_frame_buffer->clear();
	m_shader->use();
	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	scene->render();
}
