#ifndef BAUASIAN_DIRECTION_INTERFACE_HPP
#define BAUASIAN_DIRECTION_INTERFACE_HPP

#include <glm/glm.hpp>


namespace bauasian
{
	class DirectionInterface;
}

class bauasian::DirectionInterface
{
public:
	DirectionInterface(const glm::vec3& direction);

	void setDirection(const glm::vec3& direction);
	const glm::vec3 getDirection() const;

protected:
	glm::vec4 m_direction;

};


#endif /* BAUASIAN_DIRECTION_INTERFACE_HPP */
