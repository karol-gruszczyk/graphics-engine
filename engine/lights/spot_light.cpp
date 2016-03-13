#include "spot_light.h"

using engine::SpotLight;


SpotLight::SpotLight()
	: PointLight()
{}

void SpotLight::setRotation(glm::vec3 rotation)
{
	m_position = rotation;
}

glm::vec3 SpotLight::getRotation()
{
	return m_rotation;
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
