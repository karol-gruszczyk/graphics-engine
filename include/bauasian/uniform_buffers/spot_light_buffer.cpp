#include "spot_light_buffer.hpp"
#include "bauasian/glsl/bindings.glsl"

#include <glm/gtc/type_ptr.hpp>


struct alignas(16) UniformBlock
{
	glm::mat4 model_matrix;			// 0
	glm::vec4 diffuse_color;		// 64
	glm::vec4 specular_color;		// 80
	glm::vec4 position;				// 96
	glm::vec4 direction;			// 112
	glm::vec3 attenuation;			// 128
	float inner_angle;				// 140
	float outer_angle;				// 144
};

using bauasian::SpotLightBuffer;

SpotLightBuffer& bauasian::SpotLightBuffer::getInstance()
{
	static SpotLightBuffer instance;
	return instance;
}

SpotLightBuffer::SpotLightBuffer()
		: UniformBuffer(sizeof(UniformBlock), BUFFER_SPOT_LIGHT_BINDING)
{}

void SpotLightBuffer::setModelMatrix(const glm::mat4& matrix) const
{
	setSubData(0, sizeof(glm::mat4), glm::value_ptr(matrix));
}

void SpotLightBuffer::setDiffuseColor(const glm::vec3& color) const
{
	setSubData(64, sizeof(glm::vec3), glm::value_ptr(color));
}

void SpotLightBuffer::setSpecularColor(const glm::vec3& color) const
{
	setSubData(80, sizeof(glm::vec3), glm::value_ptr(color));
}

void SpotLightBuffer::setPosition(const glm::vec3& position) const
{
	setSubData(96, sizeof(glm::vec3), glm::value_ptr(position));
}

void SpotLightBuffer::setDirection(const glm::vec3& direction) const
{
	setSubData(112, sizeof(glm::vec3), glm::value_ptr(direction));
}

void SpotLightBuffer::setAttenuation(const glm::vec3& attenuation) const
{
	setSubData(128, sizeof(glm::vec3), glm::value_ptr(attenuation));
}

void SpotLightBuffer::setInnerAngle(float angle) const
{
	setSubData(140, sizeof(GLfloat), &angle);
}

void SpotLightBuffer::setOuterAngle(float angle) const
{
	setSubData(144, sizeof(GLfloat), &angle);
}
