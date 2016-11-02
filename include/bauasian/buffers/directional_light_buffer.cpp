#include "directional_light_buffer.hpp"
#include "bauasian/glsl/bindings.glsl"

#include <glm/gtc/type_ptr.hpp>


struct alignas(16) UniformBlock
{
	glm::vec3 diffuse_color;		// 0
	glm::vec3 specular_color;		// 16
	glm::vec3 direction;			// 32
};

using bauasian::DirectionalLightBuffer;

DirectionalLightBuffer::DirectionalLightBuffer()
		: UniformBuffer(sizeof(UniformBlock), BUFFER_DIRECTIONAL_LIGHT_BINDING)
{}

void DirectionalLightBuffer::setDiffuseColor(const glm::vec3& color) const
{
	setSubData(0, sizeof(glm::vec3), glm::value_ptr(color));
}

void DirectionalLightBuffer::setSpecularColor(const glm::vec3& color) const
{
	setSubData(16, sizeof(glm::vec3), glm::value_ptr(color));
}

void DirectionalLightBuffer::setDirection(const glm::vec3& direction) const
{
	setSubData(32, sizeof(glm::vec3), glm::value_ptr(direction));
}
