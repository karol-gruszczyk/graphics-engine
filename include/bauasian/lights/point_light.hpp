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
	PointLight(const glm::vec3& position, const float& range, const glm::vec3& color = { 1.f, 1.f, 1.f });
	PointLight(const glm::vec3& position, const glm::vec3& attenuation, const glm::vec3& color);

	const glm::vec3& getPosition() const;
	void setPosition(const glm::vec3& position);
	float getRange() const;
	void setRange(const float& range);
	const glm::vec3 getAttenuation() const;
	void setAttenuation(const glm::vec3& attenuation);
protected:
	glm::vec3 m_position;
	float m_range;
	float m_attenuation_constant, m_attenuation_linear, m_attenuation_quadratic;
};

#endif /* BAUASIAN_POINT_LIGHT_HPP */
