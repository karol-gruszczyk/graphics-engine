#include "light_accumulator.hpp"
#include "bauasian/glsl/bindings.glsl"


using bauasian::LightAccumulator;
using bauasian::Texture;
using bauasian::FrameBuffer;

LightAccumulator::LightAccumulator(const glm::uvec2& size, const std::shared_ptr<FrameBufferAttachment>& depth_buffer)
		: m_ambient_renderer(size), m_point_light_renderer(size), m_spot_light_renderer(size)
{
	m_accumulation_buffer = std::make_shared<Texture>(GL_RGB16F, GL_RGB, size);
	m_frame_buffer = std::make_unique<FrameBuffer>(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
														   { m_accumulation_buffer },
												   depth_buffer, size);
}

void LightAccumulator::setSize(const glm::uvec2& size)
{
	m_frame_buffer->setSize(size);
	m_ambient_renderer.setSize(size);
	m_point_light_renderer.setSize(size);
	m_spot_light_renderer.setSize(size);
}

void LightAccumulator::render(const Scene3D* scene) const
{
	m_ambient_renderer.process(m_frame_buffer.get());

	glEnable(GL_BLEND);  // setup additive blending
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	m_directional_light_renderer.render(scene);

	glCullFace(GL_FRONT);
	m_point_light_renderer.render(scene);
	m_spot_light_renderer.render(scene);
	glCullFace(GL_BACK);

	glDisable(GL_BLEND);

	m_accumulation_buffer->bind(POST_PROCESSING_COLOR_TEXTURE);
	m_accumulation_buffer->bind(POST_PROCESSING_BLOOM_COLOR_TEXTURE);
}

void LightAccumulator::enableSSAO()
{
	m_ambient_renderer.enableSSAO();
}

void LightAccumulator::disableSSAO()
{
	m_ambient_renderer.disableSSAO();
}
