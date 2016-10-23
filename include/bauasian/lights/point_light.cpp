#include "point_light.hpp"

#include <glm/gtc/matrix_transform.hpp>


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

const glm::vec3& PointLight::getPosition() const
{
	return m_position;
}

void PointLight::setPosition(const glm::vec3& position)
{
	m_model_matrix = glm::translate(m_model_matrix, (position - m_position) / m_range);
	m_position = position;
}

float PointLight::getRange() const
{
	return m_range;
}

void PointLight::setRange(const float& range)
{
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

	m_range = calculateRange();
	m_model_matrix = glm::scale(m_model_matrix, glm::vec3(m_range));
}

const glm::mat4& PointLight::getModelMatrix() const
{
	return m_model_matrix;
}

const float PointLight::calculateRange() const
{
	const float MIN = 5.f / 255.f;
	float a = MIN * m_attenuation_quadratic;
	float b = MIN * m_attenuation_linear;
	float c = MIN * m_attenuation_constant - 1;
	float delta = b * b - 4 * a * c;
	return glm::abs(-b - glm::sqrt(delta)) / (2.f * a);
}
