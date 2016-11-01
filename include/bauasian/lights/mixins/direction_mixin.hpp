#ifndef BAUASIAN_DIRECTION_MIXIN_HPP
#define BAUASIAN_DIRECTION_MIXIN_HPP

#include <glm/glm.hpp>


namespace bauasian
{
	class DirectionMixin;
}

class bauasian::DirectionMixin
{
public:
	DirectionMixin(const glm::vec3& direction);

	void setDirection(const glm::vec3& direction);
	const glm::vec3 getDirection() const;

protected:
	glm::vec4 m_direction;

};


#endif /* BAUASIAN_DIRECTION_MIXIN_HPP */
