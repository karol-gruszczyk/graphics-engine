#ifndef BAUASIAN_DIRECTIONAL_LIGHT_HPP
#define BAUASIAN_DIRECTIONAL_LIGHT_HPP

#include "light.hpp"
#include "interfaces/direction_interface.hpp"


namespace bauasian
{
	class DirectionalLight;
}

class bauasian::DirectionalLight final : public Light, public DirectionInterface
{
public:
	DirectionalLight(const glm::vec3& direction);

};

#endif /* BAUASIAN_DIRECTIONAL_LIGHT_HPP */
