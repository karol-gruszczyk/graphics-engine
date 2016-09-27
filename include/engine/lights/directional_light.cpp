#include "directional_light.hpp"


using engine::DirectionalLight;


DirectionalLight::DirectionalLight(const glm::vec3 &direction, const glm::vec3 &color /* = { 1.f, 1.f, 1.f } */,
                                   const bool &active /* = true */)
		: Light(color, active), m_direction(direction)
{}

void DirectionalLight::setDirection(const glm::vec3 &direction)
{
	m_direction = glm::normalize(direction);
}

const glm::vec3 &DirectionalLight::getDirection() const
{
	return m_direction;
}
