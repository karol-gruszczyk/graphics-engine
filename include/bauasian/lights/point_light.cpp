#include "point_light.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::PointLight;

PointLight::PointLight(const glm::vec3& position, float range)
{
	setDiffuseColor(m_diffuse_color);
	setSpecularColor(m_specular_color);
	setPosition(position);
	setRange(range);
}

PointLight::PointLight(const glm::vec3& position, const glm::vec3& attenuation)
{
	setDiffuseColor(m_diffuse_color);
	setSpecularColor(m_specular_color);
	setPosition(position);
	setAttenuation(attenuation);
}

void PointLight::bind() const
{
	m_buffer.bind();
}

void PointLight::setDiffuseColor(const glm::vec3& color)
{
	Light::setDiffuseColor(color);
	m_buffer.setDiffuseColor(m_diffuse_color);
}

void PointLight::setSpecularColor(const glm::vec3& color)
{
	Light::setSpecularColor(color);
	m_buffer.setSpecularColor(m_specular_color);
}

void PointLight::setPosition(const glm::vec3& position)
{
	PointLightMixin::setPosition(position);
	m_buffer.setPosition(m_position);
	m_buffer.setModelMatrix(m_model_matrix);
}

void PointLight::setAttenuation(const glm::vec3& attenuation)
{
	PointLightMixin::setAttenuation(attenuation);
	m_buffer.setAttenuation(m_attenuation);
}
void PointLight::calculateModelMatrix()
{
	PointLightMixin::calculateModelMatrix();
	m_buffer.setModelMatrix(m_model_matrix);
}
