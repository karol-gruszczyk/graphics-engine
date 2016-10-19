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
	Sphere(const float& radius, const unsigned& num_sides);

	const float& getRadius() const;

	void render() const override;

private:
	float m_radius;

};


#endif /* BAUASIAN_SPHERE_HPP */
