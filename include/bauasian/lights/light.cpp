#include "light.hpp"


using bauasian::Light;


Light::Light(const glm::vec3& color /* = { 1.f, 1.f, 1.f } */, const bool& active /* = true */)
		: m_color(color), m_active(active)
{}

void Light::setColor(const glm::vec3& color)
{
	m_color = color;
}

const glm::vec3& Light::getColor() const
{
	return m_color;
}

void Light::setActive(const bool& active)
{
	m_active = active;
}

bool Light::isActive() const
{
	return m_active;
}
