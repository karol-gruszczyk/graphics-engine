#ifndef BAUASIAN_POINT_LIGHT_BUFFER_HPP
#define BAUASIAN_POINT_LIGHT_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class PointLightBuffer;
}

class bauasian::PointLightBuffer : public UniformBuffer
{
public:
	static PointLightBuffer& getInstance();

private:
	PointLightBuffer();

};

#endif /* BAUASIAN_POINT_LIGHT_BUFFER_HPP */
