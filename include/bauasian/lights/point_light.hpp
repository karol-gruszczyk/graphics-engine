#ifndef BAUASIAN_POINT_LIGHT_HPP
#define BAUASIAN_POINT_LIGHT_HPP

#include "light.hpp"
#include "mixins/point_light_mixin.hpp"
#include "bauasian/buffers/point_light_buffer.hpp"


namespace bauasian
{
	class PointLight;
}

class bauasian::PointLight : public Light, public PointLightMixin
{
public:
	PointLight(const glm::vec3& position, const float& range);
	PointLight(const glm::vec3& position, const glm::vec3& attenuation);

	void bind() const;

	virtual void setDiffuseColor(const glm::vec3& color) override;
	virtual void setSpecularColor(const glm::vec3& color) override;
	virtual void setPosition(const glm::vec3& position) override;
	virtual void setAttenuation(const glm::vec3& attenuation) override;


private:
	PointLightBuffer m_buffer;

	virtual void calculateModelMatrix() override;

};

#endif /* BAUASIAN_POINT_LIGHT_HPP */
