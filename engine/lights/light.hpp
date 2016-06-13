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
	Light(const glm::vec3& color = { 1.f, 1.f, 1.f }, const bool& active = true);

	void setColor(const glm::vec3& color);
	const glm::vec3& getColor() const;
	void setActive(const bool& active);
	bool isActive() const;
protected:
	glm::vec3 m_color;
	bool m_active;
};

#endif /* LIGHT_HPP_ */
