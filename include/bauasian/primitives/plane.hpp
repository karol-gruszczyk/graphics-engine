#ifndef BAUASIAN_PLANE_HPP
#define BAUASIAN_PLANE_HPP

#include "abstract/entity_3d.hpp"


namespace bauasian
{
	class Plane;
}

class bauasian::Plane : public Entity3D
{
public:
	Plane(const glm::vec2& size, unsigned tile = 1);

	const glm::vec2& getSize() const;
	float getTile() const;
private:
	glm::vec2 m_size;
	float m_tile;
};

#endif /* BAUASIAN_PLANE_HPP */
