#include "directional_light.hpp"

using engine::DirectionalLight;


DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color /* = { 1.f, 1.f, 1.f } */, bool active /* = true */)
	: Light(color, active), m_direction(direction)
{}

void DirectionalLight::setDirection(glm::vec3 direction)
{
	m_direction = glm::normalize(direction);
}

glm::vec3 DirectionalLight::getDirection()
{
	return m_direction;
}
