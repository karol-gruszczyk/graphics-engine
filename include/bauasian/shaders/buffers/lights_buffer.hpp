#ifndef BAUASIAN_LIGHTS_BUFFER_HPP
#define BAUASIAN_LIGHTS_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class LightsBuffer;
}

class bauasian::LightsBuffer : public UniformBuffer
{
public:
	struct alignas(16) GlslLights
	{

	};

	static LightsBuffer& getInstance();

private:
	LightsBuffer();

};

#endif /* BAUASIAN_LIGHTS_BUFFER_HPP */
