#ifndef BAUASIAN_POINT_LIGHT_MIXIN_HPP
#define BAUASIAN_POINT_LIGHT_MIXIN_HPP

#include <glm/glm.hpp>


namespace bauasian
{
	class PointLightMixin;
}

class bauasian::PointLightMixin
{
public:
	const glm::vec3& getPosition() const;
	virtual void setPosition(const glm::vec3& position);

	float getRange() const;
	void setRange(float range);
	const glm::vec3& getAttenuation() const;
	virtual void setAttenuation(const glm::vec3& attenuation);

	const glm::mat4& getModelMatrix() const;

protected:
	glm::mat4 m_model_matrix;
	glm::vec3 m_position;
	float m_range;
	glm::vec3 m_attenuation;

	virtual void calculateModelMatrix();

private:
	float calculateRange() const;

};

#endif /* BAUASIAN_POINT_LIGHT_MIXIN_HPP */
