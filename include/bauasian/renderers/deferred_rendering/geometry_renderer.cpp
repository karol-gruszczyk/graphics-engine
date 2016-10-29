#include "geometry_renderer.hpp"
#include "bauasian/shaders/buffers/model_matrices_buffer.hpp"
#include "bauasian/shaders/buffers/camera_buffer.hpp"


using bauasian::GeometryRenderer;

GeometryRenderer::GeometryRenderer(const glm::uvec2& size, const std::shared_ptr<FrameBufferAttachment>& depth_buffer)
		: ShaderMixin("deferred_rendering/gbuffer_vs.glsl", "deferred_rendering/gbuffer_fs.glsl")
{
	m_albedo_buffer = std::make_shared<Texture>(GL_RGB, GL_RGB, size);
	m_specular_buffer = std::make_shared<Texture>(GL_RGBA, GL_RGBA, size);
	m_normal_buffer = std::make_shared<Texture>(GL_RGB16F, GL_RGB, size);
	m_position_buffer = std::make_shared<Texture>(GL_RGBA16F, GL_RGBA, size);
	m_frame_buffer = std::make_unique<FrameBuffer>(
			std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
					{ m_albedo_buffer, m_specular_buffer, m_normal_buffer, m_position_buffer },
			depth_buffer, size);

	Material::setShaderLocations(m_shader.get());
	ModelMatricesBuffer::getInstance().attachUniformBlock(m_shader.get(), "ModelMatrices");
	CameraBuffer::getInstance().attachUniformBlock(m_shader.get(), "CameraBuffer");
}

void GeometryRenderer::setSize(const glm::uvec2& size)
{
	m_frame_buffer->setSize(size);
}

void GeometryRenderer::render(const Scene3D* const scene) const
{
	m_frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	m_shader->use();
	glClear(GL_STENCIL_BUFFER_BIT);
	scene->render();
}

void GeometryRenderer::bindTextures() const
{
	m_albedo_buffer->bind(0);
	m_specular_buffer->bind(1);
	m_normal_buffer->bind(2);
	m_position_buffer->bind(3);
}
