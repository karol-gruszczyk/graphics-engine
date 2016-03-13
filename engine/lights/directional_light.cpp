#include "directional_light.h"

using engine::DirectionalLight;


DirectionalLight::DirectionalLight()
	: Light()
{}

DirectionalLight::DirectionalLight(glm::vec3 rotation, glm::vec3 color /* = { 1.f, 1.f, 1.f } */ )
{
	initialize(rotation, color);
}

void DirectionalLight::initialize(glm::vec3 rotation, glm::vec3 color /* = { 1.f, 1.f, 1.f } */)
{
	m_rotation = rotation;
	m_color = color;
}

void DirectionalLight::setRotation(glm::vec3 rotation)
{
	m_rotation = rotation;
}

glm::vec3 DirectionalLight::getRotation()
{
	return m_rotation;
}
