#include "geometry_pass.hpp"
#include "bauasian/glsl/bindings.glsl"


using bauasian::GeometryPass;

GeometryPass::GeometryPass(const glm::uvec2& size, const std::shared_ptr<FrameBufferAttachment>& depth_buffer)
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
}

void GeometryPass::setSize(const glm::uvec2& size)
{
	m_frame_buffer->setSize(size);
}

void GeometryPass::render(const Scene3D* const scene) const
{
	m_frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	m_shader->use();
	scene->render();

	m_albedo_buffer->bind(DEFERRED_ALBEDO_BINDING);
	m_specular_buffer->bind(DEFERRED_SPECULAR_BINDING);
	m_normal_buffer->bind(DEFERRED_NORMAL_BINDING);
	m_position_buffer->bind(DEFERRED_POSITION_BINDING);
}
