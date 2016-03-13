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

	void setRotation(glm::vec3 rotation);
	glm::vec3 getRotation();
	void setInnerAngle(float inner_angle);
	float getInnerAngle();
	void setOuterAngle(float outer_angle);
	float getOuterAngle();
private:
	glm::vec3 m_rotation;
	float m_inner_angle, m_outer_angle;
};

#endif /* SPOT_LIGHT_H_ */
