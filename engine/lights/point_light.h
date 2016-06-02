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
	PointLight(glm::vec3 position, float range, glm::vec3 color = { 1.f, 1.f, 1.f }, bool active = true);

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void setRange(float range);
	float getRange();
protected:
	glm::vec3 m_position;
	float m_range;
};

#endif /* POINT_LIGHT_H_ */
