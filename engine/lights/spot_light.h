#ifndef SPOT_LIGHT_H_
#define SPOT_LIGHT_H_

#include "point_light.h"


namespace engine
{
	class SpotLight;
}

class engine::SpotLight final : public PointLight
{
public:
	SpotLight();

	void initialize(glm::vec3 position, glm::vec3 direction, float range, float inner_angle, float outer_angle, glm::vec3 color = { 1.f, 1.f, 1.f });
	void setDirection(glm::vec3 direction);
	glm::vec3 getDirection();
	void setInnerAngle(float inner_angle);
	float getInnerAngle();
	void setOuterAngle(float outer_angle);
	float getOuterAngle();
private:
	glm::vec3 m_direction;
	float m_inner_angle, m_outer_angle;
};

#endif /* SPOT_LIGHT_H_ */
