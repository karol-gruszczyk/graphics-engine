#include "light.hpp"


using bauasian::Light;

const glm::vec3 Light::getDiffuseColor() const
{
	return (glm::vec3) m_diffuse_color;
}

void Light::setColor(const glm::vec3& diffuse, const glm::vec3& specular)
{
	setDiffuseColor(diffuse);
	setSpecularColor(specular);
}
