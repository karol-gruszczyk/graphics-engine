#include "spot_light_buffer.hpp"
#include "bauasian/lights/spot_light.hpp"


using bauasian::SpotLightBuffer;

SpotLightBuffer& bauasian::SpotLightBuffer::getInstance()
{
	static SpotLightBuffer instance;
	return instance;
}

SpotLightBuffer::SpotLightBuffer()
		: UniformBuffer(sizeof(SpotLight), UniformBuffer::SPOT_LIGHT)
{}
