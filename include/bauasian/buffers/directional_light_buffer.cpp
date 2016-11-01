#include "directional_light_buffer.hpp"
#include "bauasian/lights/directional_light.hpp"


using bauasian::DirectionalLightBuffer;

DirectionalLightBuffer& bauasian::DirectionalLightBuffer::getInstance()
{
	static DirectionalLightBuffer instance;
	return instance;
}

DirectionalLightBuffer::DirectionalLightBuffer()
		: UniformBuffer(sizeof(DirectionalLight), UniformBuffer::DIRECTIONAL_LIGHT)
{}
