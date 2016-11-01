#ifndef BAUASIAN_SPOT_LIGHT_BUFFER_HPP
#define BAUASIAN_SPOT_LIGHT_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class SpotLightBuffer;
}

class bauasian::SpotLightBuffer : public UniformBuffer
{
public:
	static SpotLightBuffer& getInstance();

private:
	SpotLightBuffer();

};

#endif /* BAUASIAN_SPOT_LIGHT_BUFFER_HPP */
