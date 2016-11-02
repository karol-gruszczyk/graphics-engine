#ifndef BAUASIAN_DIRECTIONAL_LIGHT_HPP
#define BAUASIAN_DIRECTIONAL_LIGHT_HPP

#include "light.hpp"
#include "mixins/direction_mixin.hpp"
#include "bauasian/uniform_buffers/directional_light_buffer.hpp"


namespace bauasian
{
	class DirectionalLight;
}

class bauasian::DirectionalLight final : public Light, public DirectionMixin
{
public:
	DirectionalLight(const glm::vec3& direction);

	void bind() const;

	virtual void setDiffuseColor(const glm::vec3& color) override;
	virtual void setSpecularColor(const glm::vec3& color) override;
	virtual void setDirection(const glm::vec3& direction) override;

private:
	DirectionalLightBuffer m_buffer;

};

#endif /* BAUASIAN_DIRECTIONAL_LIGHT_HPP */
