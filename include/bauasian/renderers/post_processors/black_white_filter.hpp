#ifndef BAUASIAN_ENGINE_BLACK_WHITE_FILTER_HPP
#define BAUASIAN_ENGINE_BLACK_WHITE_FILTER_HPP

#include "filter.hpp"


namespace bauasian
{
	class BlackWhiteFilter;
}

class bauasian::BlackWhiteFilter : public Filter
{
public:
	BlackWhiteFilter(const glm::vec3& color_weights = { 0.2126, 0.7152, 0.0722 });

};

#endif /* BAUASIAN_ENGINE_BLACK_WHITE_FILTER_HPP */
