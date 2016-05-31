#include "light.h"

using engine::Light;


Light::Light(glm::vec3 color /* = { 1.f, 1.f, 1.f } */, bool active /* = true */)
	: m_color(color), m_active(active)
{}

void Light::setColor(glm::vec3 color)
{
	m_color = color;
}

glm::vec3 Light::getColor()
{
	return m_color;
}

void Light::setActive(bool active)
{
	m_active = active;
}

bool Light::isActive()
{
	return m_active;
}
