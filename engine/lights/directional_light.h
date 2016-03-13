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
	DirectionalLight();
	DirectionalLight(glm::vec3 rotation, glm::vec3 color = { 1.f, 1.f, 1.f });

	void initialize(glm::vec3 rotation, glm::vec3 color = { 1.f, 1.f, 1.f });
	void setRotation(glm::vec3 rotation);
	glm::vec3 getRotation();
private:
	glm::vec3 m_rotation;
};

#endif /* DIRECTIONAL_LIGHT_H_ */
