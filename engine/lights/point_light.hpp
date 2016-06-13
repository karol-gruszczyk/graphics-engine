#ifndef POINT_LIGHT_HPP_
#define POINT_LIGHT_HPP_

#include "light.hpp"


namespace engine
{
	class PointLight;
}

class engine::PointLight : public Light
{
public:
	PointLight(const glm::vec3& position, const float& range, const glm::vec3& color = { 1.f, 1.f, 1.f }, const bool& active = true);

	void setPosition(const glm::vec3& position);
	const glm::vec3& getPosition() const;
	void setRange(const float& range);
	float getRange() const;
protected:
	glm::vec3 m_position;
	float m_range;
};

#endif /* POINT_LIGHT_HPP_ */
