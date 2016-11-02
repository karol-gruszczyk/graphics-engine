#include "shadow_renderer.hpp"
#include "bauasian/glsl/bindings.glsl"


using bauasian::ShadowRenderer;
using bauasian::Texture;

ShadowRenderer::ShadowRenderer(const glm::uvec2& size)
		: ShaderMixin("deferred_rendering/shadow_vs.glsl"), m_camera({ 20.f, 20.f }, 0.1f, 1.f)
{
	m_depth_texture = std::make_shared<Texture>(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, size, GL_FLOAT);
	m_frame_buffer = std::make_unique<FrameBuffer>(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>{},
												   m_depth_texture, size);
}

void ShadowRenderer::setSize(const glm::uvec2& size)
{
	m_frame_buffer->setSize(size);
}

void ShadowRenderer::render(const Scene3D* const scene, const PerspectiveCamera* const camera)
{
	calculateCameraBounds(camera);
	m_camera.bind(BUFFER_SHADOW_CAMERA_BINDING);
	m_frame_buffer->bind();
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	scene->render();
	glEnable(GL_DEPTH_TEST);
}

const Texture* const ShadowRenderer::getDepthTexture() const
{
	return m_depth_texture.get();
}

void ShadowRenderer::calculateCameraBounds(const PerspectiveCamera* const camera)
{

}
