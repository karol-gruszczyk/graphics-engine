#ifndef BAUASIAN_ENGINE_BLUR_HPP
#define BAUASIAN_ENGINE_BLUR_HPP


#include "area_filter.hpp"


namespace bauasian
{
	class Blur;
}

class bauasian::Blur : public AreaFilter
{
public:
	Blur(const GLuint& radius);

	const GLuint& getRadius() const;
	void setRadius(const GLuint& radius);

private:
	GLuint m_radius;

	GLint m_location_radius;
};

#endif /* BAUASIAN_ENGINE_BLUR_HPP */
