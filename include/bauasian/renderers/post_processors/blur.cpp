#include "blur.hpp"


using bauasian::Blur;

Blur::Blur(const GLuint& radius)
		: AreaFilter("post_processing/blur_fs.glsl")
{
	m_location_radius = m_shader->getUniformLocation("radius");
	setRadius(radius);
}

const GLuint& Blur::getRadius() const
{
	return m_radius;
}

void Blur::setRadius(const GLuint& radius)
{
	m_radius = radius;
	m_shader->setUniform(m_location_radius, radius);
}
