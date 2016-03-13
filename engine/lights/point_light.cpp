#include "point_light.h"

using engine::PointLight;


PointLight::PointLight()
	: Light()
{}

void PointLight::setPosition(glm::vec3 position)
{
	m_position = position;
}

glm::vec3 PointLight::getPosition()
{
	return m_position;
}

void PointLight::setRange(float range)
{
	m_range = range;
}

float PointLight::getRange()
{
	return m_range;
}
