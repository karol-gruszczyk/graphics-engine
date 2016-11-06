#include "shadow_buffer.hpp"
#include "bauasian/glsl/bindings.glsl"

#include <glm/gtc/type_ptr.hpp>


struct alignas(16) UniformBlock
{
	glm::mat4 shadow_space_matrix;		// 0
};

using bauasian::ShadowBuffer;

ShadowBuffer::ShadowBuffer()
		: UniformBuffer(sizeof(UniformBlock), BUFFER_SHADOW_BINDING)
{}

void ShadowBuffer::setShadowSpaceMatrix(const glm::mat4& matrix) const
{
	setSubData(0, sizeof(glm::mat4), glm::value_ptr(matrix));
}
