#include "point_light_buffer.hpp"
#include "bauasian/glsl/bindings.glsl"

#include <glm/gtc/type_ptr.hpp>


struct alignas(16) UniformBlock
{
	glm::mat4 model_matrix;			// 0
	glm::vec4 diffuse_color;		// 64
	glm::vec4 specular_color;		// 80
	glm::vec4 position;				// 96
	glm::vec4 attenuation;			// 112
};

using bauasian::PointLightBuffer;

PointLightBuffer::PointLightBuffer()
		: UniformBuffer(sizeof(UniformBlock), BUFFER_POINT_LIGHT_BINDING)
{}

void PointLightBuffer::setModelMatrix(const glm::mat4& matrix) const
{
	setSubData(0, sizeof(glm::mat4), glm::value_ptr(matrix));
}

void PointLightBuffer::setDiffuseColor(const glm::vec3& color) const
{
	setSubData(64, sizeof(glm::vec3), glm::value_ptr(color));
}

void PointLightBuffer::setSpecularColor(const glm::vec3& color) const
{
	setSubData(80, sizeof(glm::vec3), glm::value_ptr(color));
}

void PointLightBuffer::setPosition(const glm::vec3& position) const
{
	setSubData(96, sizeof(glm::vec3), glm::value_ptr(position));
}

void PointLightBuffer::setAttenuation(const glm::vec3& attenuation) const
{
	setSubData(112, sizeof(glm::vec3), glm::value_ptr(attenuation));
}
