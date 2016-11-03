#ifndef BAUASIAN_DIRECTIONAL_LIGHT_BUFFER_HPP
#define BAUASIAN_DIRECTIONAL_LIGHT_BUFFER_HPP

#include "uniform_buffer.hpp"


namespace bauasian
{
	class DirectionalLightBuffer;
}

class bauasian::DirectionalLightBuffer : protected UniformBuffer
{
public:
	DirectionalLightBuffer();

	using UniformBuffer::bind;

	void setDiffuseColor(const glm::vec3& color) const;
	void setSpecularColor(const glm::vec3& color) const;
	void setDirection(const glm::vec3& direction) const;
	void setUseShadowMap(const int& value) const;

};

#endif /* BAUASIAN_DIRECTIONAL_LIGHT_BUFFER_HPP */
