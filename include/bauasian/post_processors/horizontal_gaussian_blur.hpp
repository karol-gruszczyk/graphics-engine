#ifndef BAUASIAN_HORIZONTAL_GAUSSIAN_BLUR_HPP
#define BAUASIAN_HORIZONTAL_GAUSSIAN_BLUR_HPP

#include "area_filter.hpp"


namespace bauasian
{
	class HorizontalGaussianBlur;
}

class bauasian::HorizontalGaussianBlur : public AreaFilter
{
public:
	HorizontalGaussianBlur(const glm::uvec2& size);

};


#endif /* BAUASIAN_HORIZONTAL_GAUSSIAN_BLUR_HPP */
