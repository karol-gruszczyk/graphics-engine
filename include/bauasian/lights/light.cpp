#include "light.hpp"


using bauasian::Light;


const glm::vec3 Light::getAmbientColor() const
{
	return (glm::vec3) m_ambient_color;
}

void Light::setAmbientColor(const glm::vec3& color)
{
	m_ambient_color = glm::vec4(color, 0.f);
}

const glm::vec3 Light::getDiffuseColor() const
{
	return (glm::vec3) m_diffuse_color;
}

void Light::setDiffuseColor(const glm::vec3& color)
{
	m_diffuse_color = glm::vec4(color, 0.f);
}

const glm::vec3 Light::getSpecularColor() const
{
	return (glm::vec3) m_specular_color;
}

void Light::setSpecularColor(const glm::vec3& color)
{
	m_specular_color = glm::vec4(color, 0.f);
}

void Light::setColor(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
{
	setAmbientColor(ambient);
	setDiffuseColor(diffuse);
	setSpecularColor(specular);
}
