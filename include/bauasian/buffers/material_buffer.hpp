#ifndef BAUASIAN_MATERIAL_BUFFER_HPP
#define BAUASIAN_MATERIAL_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class MaterialBuffer;
}

class bauasian::MaterialBuffer : protected UniformBuffer
{
public:
	MaterialBuffer();

	using UniformBuffer::bind;

	void setDiffuseColor(const glm::vec3& color);
	void setSpecular(const glm::vec3& color);
	void setUseDiffuseTexture(const GLint& value);
	void setUseSpecularTexture(const GLint& value);
	void setUseNormalTexture(const GLint& value);
	void setUseDisplacementTexture(const GLint& value);
	void setUseOpacityTexture(const GLint& value);
	void setShininess(const float& shininess);

};


#endif /* BAUASIAN_MATERIAL_BUFFER_HPP */
