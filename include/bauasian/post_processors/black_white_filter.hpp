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
	BlackWhiteFilter(const glm::uvec2& size, GLenum storage);

};

#endif /* BAUASIAN_ENGINE_BLACK_WHITE_FILTER_HPP */
