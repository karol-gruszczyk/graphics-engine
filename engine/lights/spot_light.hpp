#ifndef SPOT_LIGHT_HPP_
#define SPOT_LIGHT_HPP_

#include "point_light.hpp"


namespace engine
{
	class SpotLight;
}

class engine::SpotLight final : public PointLight
{
public:
	SpotLight(const glm::vec3& position, const glm::vec3& direction, const float& range, const float& inner_angle, const float& outer_angle, const glm::vec3& color = { 1.f, 1.f, 1.f }, const bool& active = true);

	void setDirection(const glm::vec3& direction);
	const glm::vec3& getDirection() const;
	void setInnerAngle(const float& inner_angle);
	float getInnerAngle() const;
	void setOuterAngle(const float& outer_angle);
	float getOuterAngle() const;
private:
	glm::vec3 m_direction;
	float m_inner_angle, m_outer_angle;
};

#endif /* SPOT_LIGHT_HPP_ */
