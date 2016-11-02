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
	PointLightBuffer();

	using UniformBuffer::bind;

	void setModelMatrix(const glm::mat4& matrix) const;
	void setDiffuseColor(const glm::vec3& color) const;
	void setSpecularColor(const glm::vec3& color) const;
	void setPosition(const glm::vec3& position) const;
	void setAttenuation(const glm::vec3& attenuation) const;

};

#endif /* BAUASIAN_POINT_LIGHT_BUFFER_HPP */
