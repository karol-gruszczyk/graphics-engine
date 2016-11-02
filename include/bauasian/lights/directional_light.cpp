#include "directional_light.hpp"


using bauasian::DirectionalLight;


DirectionalLight::DirectionalLight(const glm::vec3& direction)
{
	setDirection(direction);
	setDiffuseColor(glm::vec3(m_diffuse_color));
	setSpecularColor(glm::vec3(m_specular_color));
}

void DirectionalLight::setDiffuseColor(const glm::vec3& color)
{
	Light::setDiffuseColor(color);
	m_buffer.setDiffuseColor(color);
}

void DirectionalLight::setSpecularColor(const glm::vec3& color)
{
	Light::setSpecularColor(color);
	m_buffer.setSpecularColor(color);
}

void DirectionalLight::setDirection(const glm::vec3& direction)
{
	DirectionMixin::setDirection(direction);
	m_buffer.setDirection(direction);
}

void DirectionalLight::bind() const
{
	m_buffer.bind();
}

void DirectionalLight::enableShadows(const unsigned& size)
{
	m_shadow_renderer = std::make_unique<ShadowRenderer>(glm::uvec2(size, size));
}

void DirectionalLight::disableShadows()
{
	m_shadow_renderer.reset();
}
