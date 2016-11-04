#ifndef BAUASIAN_ENGINE_VERTICAL_GAUSSIAN_BLUR_HPP
#define BAUASIAN_ENGINE_VERTICAL_GAUSSIAN_BLUR_HPP

#include "area_filter.hpp"


namespace bauasian
{
	class VerticalGaussianBlur;
}

class bauasian::VerticalGaussianBlur : public AreaFilter
{
public:
	VerticalGaussianBlur(const glm::uvec2& size, GLenum storage);

};

#endif /* BAUASIAN_ENGINE_VERTICAL_GAUSSIAN_BLUR_HPP */
