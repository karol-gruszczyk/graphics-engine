#include "directional_light.h"

using engine::DirectionalLight;


DirectionalLight::DirectionalLight()
	: Light()
{}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color /* = { 1.f, 1.f, 1.f } */ )
{
	initialize(direction, color);
}

void DirectionalLight::initialize(glm::vec3 direction, glm::vec3 color /* = { 1.f, 1.f, 1.f } */)
{
	m_direction = direction;
	m_color = color;
}

void DirectionalLight::setDirection(glm::vec3 direction)
{
	m_direction = glm::normalize(direction);
}

glm::vec3 DirectionalLight::getDirection()
{
	return m_direction;
}
