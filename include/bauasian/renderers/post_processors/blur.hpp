#ifndef BAUASIAN_ENGINE_BLUR_HPP
#define BAUASIAN_ENGINE_BLUR_HPP


#include "post_processor.hpp"


namespace bauasian
{
	class Blur;
}

class bauasian::Blur : public PostProcessor
{
public:
	Blur(const GLuint& radius);

	const GLuint& getRadius() const;
	void setRadius(const GLuint& radius);
	virtual void setContextSize(const unsigned& width, const unsigned& height) const override;

private:
	GLuint m_radius;
};

#endif /* BAUASIAN_ENGINE_BLUR_HPP */
