#ifndef BAUASIAN_DIRECTIONAL_LIGHT_BUFFER_HPP
#define BAUASIAN_DIRECTIONAL_LIGHT_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class DirectionalLightBuffer;
}

class bauasian::DirectionalLightBuffer : public UniformBuffer
{
public:
	static DirectionalLightBuffer& getInstance();

private:
	DirectionalLightBuffer();

};

#endif /* BAUASIAN_DIRECTIONAL_LIGHT_BUFFER_HPP */
