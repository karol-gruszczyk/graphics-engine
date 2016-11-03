#include "shadow_renderer.hpp"
#include "bauasian/glsl/bindings.glsl"


using bauasian::ShadowRenderer;
using bauasian::Texture;

ShadowRenderer::ShadowRenderer(const glm::uvec2& size)
		: ShaderMixin("deferred_rendering/shadow_vs.glsl"), m_camera(size, -10000.1f, 10000.f)
{
	SizeMixin::setSize(size);
	m_depth_texture = std::make_shared<Texture>(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, size, GL_FLOAT);
	m_depth_texture->enableDepthComparison();
	m_frame_buffer = std::make_unique<FrameBuffer>(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>{},
												   m_depth_texture, size);
}

void ShadowRenderer::setSize(const glm::uvec2& size)
{
	m_frame_buffer->setSize(size);
}

void ShadowRenderer::render(const Scene3D* const scene, const glm::vec3& light_direction)
{
	calculateCameraBounds(light_direction);
	m_frame_buffer->bind();
	glViewport(0, 0, m_size.x, m_size.y);
	m_camera.bind(BUFFER_SHADOW_CAMERA_BINDING);
	m_shader->use();
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	scene->render();
	glDisable(GL_DEPTH_TEST);
}

void ShadowRenderer::bind() const
{
	m_camera.bind(BUFFER_SHADOW_CAMERA_BINDING);
	m_depth_texture->bind(DEFERRED_SHADOW_MAP_BINDING);
}

void ShadowRenderer::calculateCameraBounds(const glm::vec3& light_dir)
{
	m_camera.setNear(-10000.f);
	m_camera.setFar(10000.f);
	m_camera.lookAt(glm::vec3(0.f), light_dir, glm::vec3(0.f, 1.f, 0.f));
}
