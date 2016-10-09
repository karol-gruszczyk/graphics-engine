#include "spot_light.hpp"


using bauasian::SpotLight;


SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, const float& range,
                     const float& inner_angle, const float& outer_angle)
		: PointLight(position, range), DirectionInterface(direction), m_inner_angle(inner_angle)
{
	setOuterAngle(outer_angle);
}

SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& attenuation,
                     const float& inner_angle, const float& outer_angle)
		: PointLight(position, attenuation), DirectionInterface(direction), m_inner_angle(inner_angle)
{
	setOuterAngle(outer_angle);
}

float SpotLight::getInnerAngle() const
{
	return m_inner_angle;
}

void SpotLight::setInnerAngle(const float& inner_angle)
{
	m_inner_angle = inner_angle;
}

float SpotLight::getOuterAngle() const
{
	return m_outer_angle;
}

void SpotLight::setOuterAngle(const float& outer_angle)
{
	if (outer_angle <= m_inner_angle)
		m_outer_angle = m_inner_angle + 0.001f;
	else
		m_outer_angle = outer_angle;
}
