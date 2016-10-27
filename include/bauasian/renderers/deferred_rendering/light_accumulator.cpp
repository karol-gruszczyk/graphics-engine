#include "light_accumulator.hpp"


using bauasian::LightAccumulator;

LightAccumulator::LightAccumulator(const glm::uvec2& size, const std::shared_ptr<FrameBufferAttachment>& depth_buffer)
		: m_size(size)
{

	m_frame_buffer = new FrameBuffer(std::initializer_list<std::shared_ptr<FrameBufferAttachment>>
											 { m_accumulation_buffer },
									 depth_buffer, size);
}

LightAccumulator::~LightAccumulator()
{
	delete m_frame_buffer;
}

void LightAccumulator::setSize(const glm::uvec2& size)
{
	m_size = size;
	m_frame_buffer->setSize(size);
}

void LightAccumulator::render(const Scene3D* const scene)
{

}
