#include "spot_light.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>


using bauasian::SpotLight;

SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, const float& range,
                     const float& inner_angle, const float& outer_angle)
		: PointLight(position, range)
{
	setDirection(direction);
	setInnerAngle(inner_angle);
	setOuterAngle(outer_angle);
	calculateModelMatrix();
}

SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& attenuation,
                     const float& inner_angle, const float& outer_angle)
		: PointLight(position, attenuation)
{
	setDirection(direction);
	setInnerAngle(inner_angle);
	setOuterAngle(outer_angle);
	calculateModelMatrix();
}

float SpotLight::getInnerAngle() const
{
	return m_inner_angle;
}

void SpotLight::setInnerAngle(const float& inner_angle)
{
	m_inner_angle = inner_angle;
}

float SpotLight::getOuterAngle() const
{
	return m_outer_angle;
}

void SpotLight::setOuterAngle(const float& outer_angle)
{
	if (outer_angle <= m_inner_angle)
		m_outer_angle = m_inner_angle + 0.001f;
	else
		m_outer_angle = outer_angle;
}

void SpotLight::calculateModelMatrix()
{
	float base_radius = glm::tan(m_outer_angle);
	glm::vec3 rot_axis = glm::cross(glm::vec3(0.f, -1.f, 0.f), getDirection());
	m_model_matrix = glm::rotate(m_model_matrix, (float)glm::asin(glm::length(rot_axis)), rot_axis);
	m_model_matrix = glm::scale(m_model_matrix, glm::vec3(base_radius, 1.f, base_radius));
}
