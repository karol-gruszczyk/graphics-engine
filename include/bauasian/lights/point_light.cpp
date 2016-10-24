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

const glm::vec3& PointLight::getAttenuation() const
{
	return m_attenuation;
}

void PointLight::setAttenuation(const glm::vec3& attenuation)
{
	m_attenuation = attenuation;

	m_range = calculateRange();
	m_model_matrix = glm::scale(m_model_matrix, glm::vec3(m_range));
}

const glm::mat4& PointLight::getModelMatrix() const
{
	return m_model_matrix;
}

const float PointLight::calculateRange() const
{
	const float threshold = 0.01f;
	float a = threshold * m_attenuation.z;
	float b = threshold * m_attenuation.y;
	float c = threshold * m_attenuation.x - 1;
	float delta = b * b - 4 * a * c;
	return glm::abs(-b - glm::sqrt(delta)) / (2.f * a);
}
