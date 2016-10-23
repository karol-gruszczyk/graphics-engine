#ifndef BAUASIAN_POINT_LIGHT_HPP
#define BAUASIAN_POINT_LIGHT_HPP

#include "light.hpp"


namespace bauasian
{
	class PointLight;
}

class bauasian::PointLight : public Light
{
public:
	PointLight(const glm::vec3& position, const float& range);
	PointLight(const glm::vec3& position, const glm::vec3& attenuation);

	const glm::vec3& getPosition() const;
	void setPosition(const glm::vec3& position);
	float getRange() const;
	void setRange(const float& range);
	const glm::vec3 getAttenuation() const;
	void setAttenuation(const glm::vec3& attenuation);
	const glm::mat4& getModelMatrix() const;

protected:
	glm::vec3 m_position;
	glm::mat4 m_model_matrix;
	float m_range;
	float m_attenuation_constant, m_attenuation_linear, m_attenuation_quadratic;

	const float calculateRange() const;

};

#endif /* BAUASIAN_POINT_LIGHT_HPP */
