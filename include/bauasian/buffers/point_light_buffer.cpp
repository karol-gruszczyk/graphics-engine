#include "point_light_buffer.hpp"
#include "bauasian/lights/point_light.hpp"


using bauasian::PointLightBuffer;

PointLightBuffer& bauasian::PointLightBuffer::getInstance()
{
	static PointLightBuffer instance;
	return instance;
}

PointLightBuffer::PointLightBuffer()
		: UniformBuffer(sizeof(PointLight), UniformBuffer::POINT_LIGHT)
{}
