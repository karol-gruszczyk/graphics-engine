#ifndef GRAPHICS_ENGINE_LIGHT_HPP
#define GRAPHICS_ENGINE_LIGHT_HPP

#include <glm/glm.hpp>


namespace bauasian
{
	class Light;
}

class bauasian::Light
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

#endif /* GRAPHICS_ENGINE_LIGHT_HPP */
