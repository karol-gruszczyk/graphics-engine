#include "direction_mixin.hpp"


using bauasian::DirectionMixin;

DirectionMixin::DirectionMixin(const glm::vec3& direction)
{
	setDirection(direction);
}

void DirectionMixin::setDirection(const glm::vec3& direction)
{
	m_direction = glm::vec4(glm::normalize(direction), 0.f);
}

const glm::vec3 DirectionMixin::getDirection() const
{
	return (glm::vec3) m_direction;
}
