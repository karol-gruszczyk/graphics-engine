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

	void setDiffuseColor(const glm::vec3& color) const;
	void setSpecularColor(const glm::vec3& color) const;
	void setUseDiffuseTexture(const GLint& value) const;
	void setUseSpecularTexture(const GLint& value) const;
	void setUseNormalTexture(const GLint& value) const;
	void setUseDisplacementTexture(const GLint& value) const;
	void setUseOpacityTexture(const GLint& value) const;
	void setShininess(const float& shininess) const;

};


#endif /* BAUASIAN_MATERIAL_BUFFER_HPP */
