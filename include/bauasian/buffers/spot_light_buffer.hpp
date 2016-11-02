#ifndef BAUASIAN_SPOT_LIGHT_BUFFER_HPP
#define BAUASIAN_SPOT_LIGHT_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class SpotLightBuffer;
}

class bauasian::SpotLightBuffer : public UniformBuffer
{
public:
	SpotLightBuffer();

	using UniformBuffer::bind;

	static SpotLightBuffer& getInstance();

	void setModelMatrix(const glm::mat4& matrix) const;
	void setDiffuseColor(const glm::vec3& color) const;
	void setSpecularColor(const glm::vec3& color) const;
	void setPosition(const glm::vec3& position) const;
	void setDirection(const glm::vec3& direction) const;
	void setAttenuation(const glm::vec3& attenuation) const;
	void setInnerAngle(const float& angle) const;
	void setOuterAngle(const float& angle) const;

};

#endif /* BAUASIAN_SPOT_LIGHT_BUFFER_HPP */
