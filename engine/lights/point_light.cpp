#include "point_light.h"

using engine::PointLight;


PointLight::PointLight()
	: Light()
{}

engine::PointLight::PointLight(glm::vec3 position, float range, glm::vec3 color /* = { 1.f, 1.f, 1.f } */)
{
	initialize(position, range, color);
}

void engine::PointLight::initialize(glm::vec3 position, float range, glm::vec3 color /* = { 1.f, 1.f, 1.f } */)
{
	m_position = position;
	m_range = range;
	m_color = color;
}

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
