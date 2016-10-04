#include "blur.hpp"


using bauasian::Blur;

Blur::Blur(const GLuint& radius)
		: PostProcessor("blur_fs.glsl")
{
	setRadius(radius);
}

const GLuint& Blur::getRadius() const
{
	return m_radius;
}

void Blur::setRadius(const GLuint& radius)
{
	m_radius = radius;
	m_shader->setUniformUInt("radius", radius);
}

void Blur::setContextSize(const unsigned& width, const unsigned& height) const
{
	PostProcessor::setContextSize(width, height);
	m_shader->setUniformVector2("offset", { 1.f / width, 1.f / height });
}
