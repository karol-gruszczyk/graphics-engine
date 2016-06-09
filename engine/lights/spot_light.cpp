#include "spot_light.hpp"

using engine::SpotLight;


SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float range, float inner_angle, float outer_angle, 
	glm::vec3 color /* = { 1.f, 1.f, 1.f */, bool active /* = true */)
	: PointLight(position, range, color, active), m_direction(direction), m_inner_angle(inner_angle), 
	m_outer_angle(inner_angle + (outer_angle == 0.f ? 0.001f : outer_angle))
{}

void SpotLight::setDirection(glm::vec3 direction)
{
	m_direction = direction;
}

glm::vec3 SpotLight::getDirection()
{
	return m_direction;
}

void SpotLight::setInnerAngle(float inner_angle)
{
	m_inner_angle = inner_angle;
}

float SpotLight::getInnerAngle()
{
	return m_inner_angle;
}

void SpotLight::setOuterAngle(float outer_angle)
{
	m_outer_angle = outer_angle;
}

float SpotLight::getOuterAngle()
{
	return m_outer_angle;
}
