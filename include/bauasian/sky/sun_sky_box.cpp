#include "sun_sky_box.hpp"


using bauasian::SunSkyBox;

SunSkyBox::SunSkyBox(const glm::vec3 light_direction)
		: SkyBox("skybox/sun_fs.glsl")
{
	m_location_light_direction = m_shader_program->getUniformLocation("light_direction");
	setLightDirection(light_direction);
}

const glm::vec3& SunSkyBox::getLightDirection() const
{
	return m_light_direction;
}

void SunSkyBox::setLightDirection(const glm::vec3 light_direction)
{
	m_light_direction = glm::normalize(light_direction);
	m_shader_program->setUniform(m_location_light_direction, m_light_direction);
}
