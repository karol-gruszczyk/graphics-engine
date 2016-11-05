#include "direction_mixin.hpp"


using bauasian::DirectionMixin;

void DirectionMixin::setDirection(const glm::vec3& direction)
{
	m_direction = glm::normalize(direction);
}
