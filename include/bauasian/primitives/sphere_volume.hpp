#ifndef BAUASIAN_SPHERE_VOLUME_HPP
#define BAUASIAN_SPHERE_VOLUME_HPP

#include "abstract/entity_3d.hpp"


namespace bauasian
{
	class SphereVolume;
}

class bauasian::SphereVolume : public Entity3D
{
public:
	SphereVolume(const unsigned& num_sides = 12);

};

#endif /* BAUASIAN_SPHERE_VOLUME_HPP */
