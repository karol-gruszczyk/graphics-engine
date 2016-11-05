#ifndef BAUASIAN_SUN_SKY_BOX_HPP
#define BAUASIAN_SUN_SKY_BOX_HPP

#include "sky_box.hpp"


namespace bauasian
{
	class SunSkyBox;
}

class bauasian::SunSkyBox : public SkyBox
{
public:
	SunSkyBox(const glm::vec3 light_direction);

	const glm::vec3& getLightDirection() const
	{ return m_light_direction; }
	void setLightDirection(const glm::vec3 light_direction);

private:
	glm::vec3 m_light_direction;

	GLint m_location_light_direction;

};


#endif /* BAUASIAN_SUN_SKY_BOX_HPP */
