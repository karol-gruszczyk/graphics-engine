#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include "light.h"


namespace engine
{
	class PointLight;
}

class engine::PointLight : public Light
{
public:
	PointLight();

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void setRange(float range);
	float getRange();
protected:
	glm::vec3 m_position;
	float m_range;
};

#endif /* POINT_LIGHT_H_ */
