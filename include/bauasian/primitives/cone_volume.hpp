#ifndef BAUASIAN_CONE_VOLUME_HPP
#define BAUASIAN_CONE_VOLUME_HPP

#include "abstract/entity_3d.hpp"


namespace bauasian
{
	class ConeVolume;
}

class bauasian::ConeVolume : public Entity3D
{
public:
	ConeVolume(unsigned num_sides = 12);

};

#endif /* BAUASIAN_CONE_VOLUME_HPP */
