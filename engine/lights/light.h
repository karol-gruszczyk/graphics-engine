#ifndef LIGHT_H_
#define LIGHT_H_

#include <glm/glm.hpp>


namespace engine
{
	class Light;
}

class engine::Light abstract
{
public:
	Light();

	void setColor(glm::vec3 color);
	glm::vec3 getColor();
	void setActive(bool active);
	bool isActive();
protected:
	glm::vec3 m_color;
	bool m_active;
};

#endif /* LIGHT_H_ */
