#ifndef DIRECTIONAL_LIGHT_HPP_
#define DIRECTIONAL_LIGHT_HPP_

#include "light.hpp"


namespace engine
{
	class DirectionalLight;
}

class engine::DirectionalLight final : public Light
{
public:
	DirectionalLight(const glm::vec3& direction, const glm::vec3& color = { 1.f, 1.f, 1.f }, const bool& active = true);

	void setDirection(const glm::vec3& direction);
	const glm::vec3& getDirection() const;
private:
	glm::vec3 m_direction;
};

#endif /* DIRECTIONAL_LIGHT_HPP_ */
