#ifndef BAUASIAN_SPOT_LIGHT_HPP
#define BAUASIAN_SPOT_LIGHT_HPP

#include "point_light.hpp"
#include "bauasian/lights/mixins/direction_mixin.hpp"


namespace bauasian
{
	class SpotLight;
}

class bauasian::SpotLight final : public PointLight, public DirectionMixin
{
public:
	SpotLight(const glm::vec3& position, const glm::vec3& direction, float range, float inner_angle, float outer_angle);
	SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& attenuation,
			  float inner_angle, float outer_angle);

	float getInnerAngle() const;
	void setInnerAngle(float inner_angle);
	float getOuterAngle() const;
	void setOuterAngle(float outer_angle);

private:
	float m_inner_angle, m_outer_angle;

	void calculateModelMatrix();

};

#endif /* BAUASIAN_SPOT_LIGHT_HPP */
