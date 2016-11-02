#include "light.hpp"


using bauasian::Light;

const glm::vec3 Light::getDiffuseColor() const
{
	return (glm::vec3) m_diffuse_color;
}

void Light::setDiffuseColor(const glm::vec3& color)
{
	m_diffuse_color = color;
}

const glm::vec3 Light::getSpecularColor() const
{
	return (glm::vec3) m_specular_color;
}

void Light::setSpecularColor(const glm::vec3& color)
{
	m_specular_color = color;
}

void Light::setColor(const glm::vec3& diffuse, const glm::vec3& specular)
{
	setDiffuseColor(diffuse);
	setSpecularColor(specular);
}
