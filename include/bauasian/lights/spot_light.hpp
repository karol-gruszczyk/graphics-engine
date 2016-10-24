#ifndef BAUASIAN_SPOT_LIGHT_HPP
#define BAUASIAN_SPOT_LIGHT_HPP

#include "point_light.hpp"
#include "interfaces/direction_interface.hpp"


namespace bauasian
{
	class SpotLight;
}

class bauasian::SpotLight final : public PointLight, public DirectionInterface
{
public:
	SpotLight(const glm::vec3& position, const glm::vec3& direction, const float& range, const float& inner_angle,
	          const float& outer_angle);
	SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& attenuation,
	          const float& inner_angle, const float& outer_angle);

	float getInnerAngle() const;
	void setInnerAngle(const float& inner_angle);
	float getOuterAngle() const;
	void setOuterAngle(const float& outer_angle);

private:
	float m_inner_angle, m_outer_angle;

	void calculateModelMatrix();

};

#endif /* BAUASIAN_SPOT_LIGHT_HPP */
