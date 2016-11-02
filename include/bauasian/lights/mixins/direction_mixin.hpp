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
	virtual void setDirection(const glm::vec3& direction);
	const glm::vec3& getDirection() const;

protected:
	glm::vec3 m_direction;

};


#endif /* BAUASIAN_DIRECTION_MIXIN_HPP */
