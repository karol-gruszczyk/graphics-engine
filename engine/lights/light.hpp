#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include <glm/glm.hpp>


namespace engine
{
	class Light;
}

class engine::Light abstract
{
public:
	Light(glm::vec3 color = { 1.f, 1.f, 1.f }, bool active = true);

	void setColor(glm::vec3 color);
	glm::vec3 getColor();
	void setActive(bool active);
	bool isActive();
protected:
	glm::vec3 m_color;
	bool m_active;
};

#endif /* LIGHT_HPP_ */
