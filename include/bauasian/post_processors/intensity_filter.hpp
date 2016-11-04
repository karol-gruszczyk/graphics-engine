#ifndef BAUASIAN_INTENSITY_FILTER_HPP
#define BAUASIAN_INTENSITY_FILTER_HPP

#include "filter.hpp"


namespace bauasian
{
	class IntensityFilter;
}

class bauasian::IntensityFilter : public Filter
{
public:
	IntensityFilter(const glm::uvec2& size, GLenum storage);

};

#endif /* BAUASIAN_INTENSITY_FILTER_HPP */
