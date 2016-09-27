#include "spot_light.hpp"


using engine::SpotLight;


SpotLight::SpotLight(const glm::vec3 &position, const glm::vec3 &direction, const float &range,
                     const float &inner_angle, const float &outer_angle,
                     const glm::vec3 &color /* = { 1.f, 1.f, 1.f */, const bool &active /* = true */)
		: PointLight(position, range, color, active), m_direction(direction), m_inner_angle(inner_angle),
		  m_outer_angle(inner_angle + (outer_angle == 0.f ? 0.001f : outer_angle))
{}

void SpotLight::setDirection(const glm::vec3 &direction)
{
	m_direction = direction;
}

const glm::vec3 &SpotLight::getDirection() const
{
	return m_direction;
}

void SpotLight::setInnerAngle(const float &inner_angle)
{
	m_inner_angle = inner_angle;
}

float SpotLight::getInnerAngle() const
{
	return m_inner_angle;
}

void SpotLight::setOuterAngle(const float &outer_angle)
{
	m_outer_angle = outer_angle;
}

float SpotLight::getOuterAngle() const
{
	return m_outer_angle;
}
