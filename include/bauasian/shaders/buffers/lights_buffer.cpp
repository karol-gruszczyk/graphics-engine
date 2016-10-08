#include "lights_buffer.hpp"


using bauasian::LightsBuffer;

LightsBuffer::LightsBuffer()
		: UniformBuffer(sizeof(GlslLights), UniformBuffer::LIGHTS)
{}

LightsBuffer& LightsBuffer::getInstance()
{
	static LightsBuffer instance;
	return instance;
}
