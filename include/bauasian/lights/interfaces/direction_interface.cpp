#include "direction_interface.hpp"


using bauasian::DirectionInterface;

DirectionInterface::DirectionInterface(const glm::vec3& direction)
{
	setDirection(direction);
}

void DirectionInterface::setDirection(const glm::vec3& direction)
{
	m_direction = glm::vec4(glm::normalize(direction), 0.f);
}

const glm::vec3 DirectionInterface::getDirection() const
{
	return (glm::vec3) m_direction;
}
