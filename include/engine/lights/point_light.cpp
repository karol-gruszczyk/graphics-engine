#include "point_light.hpp"


using engine::PointLight;


PointLight::PointLight(const glm::vec3 &position, const float &range, const glm::vec3 &color /* = { 1.f, 1.f, 1.f } */,
                       const bool &active /* = true */)
		: Light(color, active), m_position(position), m_range(range)
{}

void PointLight::setPosition(const glm::vec3 &position)
{
	m_position = position;
}

const glm::vec3 &PointLight::getPosition() const
{
	return m_position;
}

void PointLight::setRange(const float &range)
{
	m_range = range;
}

float PointLight::getRange() const
{
	return m_range;
}
