#ifndef BAUASIAN_DIRECTIONAL_LIGHT_HPP
#define BAUASIAN_DIRECTIONAL_LIGHT_HPP

#include "light.hpp"


namespace bauasian
{
	class DirectionalLight;
}

class bauasian::DirectionalLight final : public Light
{
public:
	DirectionalLight(const glm::vec3& direction, const glm::vec3& color = { 1.f, 1.f, 1.f });

	void setDirection(const glm::vec3& direction);
	const glm::vec3& getDirection() const;
private:
	glm::vec3 m_direction;
};

#endif /* BAUASIAN_DIRECTIONAL_LIGHT_HPP */
