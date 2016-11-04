#include "point_light_mixin.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::PointLightMixin;

const glm::vec3& PointLightMixin::getPosition() const
{
	return m_position;
}

void PointLightMixin::setPosition(const glm::vec3& position)
{
	m_model_matrix = glm::translate(m_model_matrix, (position - m_position) / m_range);
	m_position = position;
}

float PointLightMixin::getRange() const
{
	return m_range;
}

void PointLightMixin::setRange(float range)
{
	setAttenuation({ 1.f, 2.f / range, 1.f / (range * range) });
	calculateModelMatrix();
}

const glm::vec3& PointLightMixin::getAttenuation() const
{
	return m_attenuation;
}

void PointLightMixin::setAttenuation(const glm::vec3& attenuation)
{
	m_attenuation = attenuation;
	m_range = calculateRange();
}

const glm::mat4& PointLightMixin::getModelMatrix() const
{
	return m_model_matrix;
}

void PointLightMixin::calculateModelMatrix()
{
	m_model_matrix = glm::scale(m_model_matrix, glm::vec3(m_range));
}

float PointLightMixin::calculateRange() const
{
	const float threshold = 0.01f;
	float a = threshold * m_attenuation.z;
	float b = threshold * m_attenuation.y;
	float c = threshold * m_attenuation.x - 1;
	float delta = b * b - 4 * a * c;
	return glm::abs(-b - glm::sqrt(delta)) / (2.f * a);
}
