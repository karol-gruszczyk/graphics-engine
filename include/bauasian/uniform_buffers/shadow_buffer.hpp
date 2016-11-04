#ifndef BAUASIAN_SHADOW_BUFFER_HPP
#define BAUASIAN_SHADOW_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class ShadowBuffer;
}

class bauasian::ShadowBuffer : protected UniformBuffer
{
public:
	ShadowBuffer();

	using UniformBuffer::bind;

	void setShadowSpaceMatrix(const glm::mat4& matrix) const;
	void setShadowPixelSize(const float& size) const;

};


#endif /* BAUASIAN_SHADOW_BUFFER_HPP */
