#ifndef DIRECTIONAL_LIGHT_H_
#define DIRECTIONAL_LIGHT_H_

#include "light.h"


namespace engine
{
	class DirectionalLight;
}

class engine::DirectionalLight final : public Light
{
public:
	DirectionalLight(glm::vec3 direction, glm::vec3 color = { 1.f, 1.f, 1.f }, bool active = true);

	void setDirection(glm::vec3 direction);
	glm::vec3 getDirection();
private:
	glm::vec3 m_direction;
};

#endif /* DIRECTIONAL_LIGHT_H_ */
