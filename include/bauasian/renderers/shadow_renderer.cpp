#include "shadow_renderer.hpp"
#include "bauasian/glsl/bindings.glsl"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::ShadowRenderer;
using bauasian::Texture;

ShadowRenderer::ShadowRenderer(unsigned size, float distance)
		: ShaderMixin("deferred_rendering/shadow_vs.glsl", "deferred_rendering/shadow_fs.glsl"),
		  m_distance(distance / 2.f),
		  m_vertical_blur(glm::uvec2(size), GL_RG32F), m_horizontal_blur(glm::uvec2(size), GL_RG32F)
{
	SizeMixin::setSize(size);
	m_depth_texture = std::make_shared<Texture>(GL_RG32F, GL_RG, glm::uvec2(size), GL_FLOAT);
	m_frame_buffer = std::make_unique<FrameBuffer>(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
														   { m_depth_texture },
												   std::make_shared<RenderBuffer>(glm::uvec2(size)), glm::uvec2(size));
}

void ShadowRenderer::setSize(const unsigned& size)
{
	SizeMixin::setSize(size);
	m_frame_buffer->setSize(glm::uvec2(size));
}

void ShadowRenderer::setDistance(float distance)
{
	m_distance = distance / 2.f;
}

void ShadowRenderer::render(const Scene3D* scene, const glm::vec3& light_direction)
{
	calculateCameraBounds(light_direction, scene->getCamera());
	m_frame_buffer->bind();
	glViewport(0, 0, m_size, m_size);
	m_buffer.bind();
	m_shader->use();
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	scene->render();
	glDisable(GL_DEPTH_TEST);

	m_vertical_blur.process(m_depth_texture.get());
	m_horizontal_blur.process(m_vertical_blur.getTexture());
}

void ShadowRenderer::bind() const
{
	m_buffer.bind();
	m_horizontal_blur.getTexture()->bind(DEFERRED_SHADOW_MAP_BINDING);
}

void ShadowRenderer::calculateCameraBounds(const glm::vec3& light_dir, const Camera* camera)
{
	auto position = camera->getPosition() + m_distance * camera->getDirection();

	auto view_matrix = glm::lookAt(position, position + light_dir, glm::vec3(0.f, 1.f, 0.f));


	const auto projection_matrix = glm::ortho(-m_distance, m_distance,
											  -m_distance, m_distance,
											  -10000.f, 10000.f);
	m_buffer.setShadowSpaceMatrix(projection_matrix * view_matrix);
}
