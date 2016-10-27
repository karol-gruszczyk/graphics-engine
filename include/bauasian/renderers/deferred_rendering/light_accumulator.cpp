#include "light_accumulator.hpp"


using bauasian::LightAccumulator;
using bauasian::Texture;

LightAccumulator::LightAccumulator(const glm::uvec2& size, const std::shared_ptr<FrameBufferAttachment>& depth_buffer)
		: m_point_light_renderer(size), m_spot_light_renderer(size)
{
	m_accumulation_buffer = std::make_shared<Texture>(GL_RGB16F, GL_RGB, size);
	m_frame_buffer = std::make_unique<FrameBuffer>(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
														   { m_accumulation_buffer },
												   depth_buffer, size);

	initializeTextureLocations(m_directional_light_renderer.getShader());
	initializeTextureLocations(m_point_light_renderer.getShader());
	initializeTextureLocations(m_spot_light_renderer.getShader());
}

void LightAccumulator::setSize(const glm::uvec2& size)
{
	m_frame_buffer->setSize(size);
	m_point_light_renderer.setSize(size);
	m_spot_light_renderer.setSize(size);
}

void LightAccumulator::render(const Scene3D* const scene) const
{
	m_frame_buffer->bind();
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);  // setup additive blending
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	m_directional_light_renderer.render(scene);

	glCullFace(GL_FRONT);
	m_point_light_renderer.render(scene);
	m_spot_light_renderer.render(scene);
	glCullFace(GL_BACK);

	glDisable(GL_BLEND);
}

const Texture* const LightAccumulator::getTexture() const
{
	return m_accumulation_buffer.get();
}

void LightAccumulator::initializeTextureLocations(const ShaderProgram* const shader) const
{
	shader->setUniform(shader->getUniformLocation("albedo_buffer"), 0);
	shader->setUniform(shader->getUniformLocation("specular_buffer"), 1);
	shader->setUniform(shader->getUniformLocation("normal_buffer"), 2);
	shader->setUniform(shader->getUniformLocation("position_buffer"), 3);
}
