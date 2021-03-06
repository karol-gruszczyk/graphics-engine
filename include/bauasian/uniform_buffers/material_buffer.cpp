#include "material_buffer.hpp"
#include "bauasian/glsl/bindings.glsl"

#include <glm/gtc/type_ptr.hpp>


struct alignas(16) UniformBlock
{
	glm::vec4 diffuse_color;					// 0
	glm::vec4 specular_color;					// 16

	GLint use_diffuse_texture;					// 32
	GLint use_specular_texture;					// 36
	GLint use_normal_texture;					// 40
	GLint use_displacement_texture;				// 44
	GLint use_opacity_texture;					// 48

	float shininess;							// 52
};

using bauasian::MaterialBuffer;

MaterialBuffer::MaterialBuffer()
		: UniformBuffer(sizeof(UniformBlock), BUFFER_MATERIAL_BINDING)
{}

void MaterialBuffer::setDiffuseColor(const glm::vec3& color) const
{
	setSubData(0, sizeof(glm::vec3), glm::value_ptr(color));
}

void MaterialBuffer::setSpecularColor(const glm::vec3& color) const
{
	setSubData(16, sizeof(glm::vec3), glm::value_ptr(color));
}

void MaterialBuffer::setUseDiffuseTexture(GLint value) const
{
	setSubData(32, sizeof(GLint), &value);
}

void MaterialBuffer::setUseSpecularTexture(GLint value) const
{
	setSubData(36, sizeof(GLint), &value);
}

void MaterialBuffer::setUseNormalTexture(GLint value) const
{
	setSubData(40, sizeof(GLint), &value);
}

void MaterialBuffer::setUseDisplacementTexture(GLint value) const
{
	setSubData(44, sizeof(GLint), &value);
}

void MaterialBuffer::setUseOpacityTexture(GLint value) const
{
	setSubData(48, sizeof(GLint), &value);
}

void MaterialBuffer::setShininess(float shininess) const
{
	setSubData(52, sizeof(GLfloat), &shininess);
}
