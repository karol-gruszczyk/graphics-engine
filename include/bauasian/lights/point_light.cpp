#include "point_light.hpp"


using bauasian::PointLight;


PointLight::PointLight(const glm::vec3& position, const float& range)
{
	setRange(range);
	setPosition(position);
}

PointLight::PointLight(const glm::vec3& position, const glm::vec3& attenuation)
{
	setAttenuation(attenuation);
	setPosition(position);
}

const glm::vec3 PointLight::getPosition() const
{
	return (glm::vec3) m_position;
}

void PointLight::setPosition(const glm::vec3& position)
{
	m_position = glm::vec4(position, 0.f);
}

float PointLight::getRange() const
{
	return m_range;
}

void PointLight::setRange(const float& range)
{
	m_range = range;
	setAttenuation({ 1.f, 2.f / range, 1.f / (range * range) });
}

const glm::vec3 PointLight::getAttenuation() const
{
	return { m_attenuation_constant, m_attenuation_linear, m_attenuation_quadratic };
}

void PointLight::setAttenuation(const glm::vec3& attenuation)
{
	m_attenuation_constant = attenuation.x;
	m_attenuation_linear = attenuation.y;
	m_attenuation_quadratic = attenuation.z;
	m_range = 1.f / m_attenuation_linear;
}
