#include "light.hpp"


using bauasian::Light;


Light::Light(const glm::vec3& color /* = { 1.f, 1.f, 1.f } */)
		: m_color(color)
{}

void Light::setColor(const glm::vec3& color)
{
	m_color = color;
}

const glm::vec3& Light::getColor() const
{
	return m_color;
}
