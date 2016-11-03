#include "directional_light.hpp"
#include "bauasian/glsl/bindings.glsl"


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
	if (m_shadow_renderer)
		m_shadow_renderer->bind();
}

void DirectionalLight::enableShadows(const unsigned& size)
{
	m_shadow_renderer = std::make_unique<ShadowRenderer>(glm::uvec2(size, size));
	m_buffer.setUseShadowMap(true);
}

void DirectionalLight::disableShadows()
{
	m_shadow_renderer.reset();
	m_buffer.setUseShadowMap(false);
}

void DirectionalLight::updateShadowMap(const bauasian::Scene3D* const scene)
{
	if (m_shadow_renderer)
		m_shadow_renderer->render(scene, m_direction);
}
