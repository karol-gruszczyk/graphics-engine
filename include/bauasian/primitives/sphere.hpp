#ifndef BAUASIAN_SPHERE_HPP
#define BAUASIAN_SPHERE_HPP

#include "abstract/entity_3d.hpp"


namespace bauasian
{
	class Sphere;
}

class bauasian::Sphere : public Entity3D
{
public:
	Sphere(float radius, unsigned num_sides);

	float getRadius() const
	{ return m_radius; }

private:
	float m_radius;

};


#endif /* BAUASIAN_SPHERE_HPP */
