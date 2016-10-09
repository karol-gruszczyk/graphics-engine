#include "directional_light.hpp"


using bauasian::DirectionalLight;


DirectionalLight::DirectionalLight(const glm::vec3& direction)
		: DirectionInterface(direction)
{}
