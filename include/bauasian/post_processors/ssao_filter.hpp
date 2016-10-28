#ifndef BAUASIAN_SSAO_FILTER_HPP
#define BAUASIAN_SSAO_FILTER_HPP

#include "area_filter.hpp"


namespace bauasian
{
	class SSAOFilter;
}

class bauasian::SSAOFilter : public AreaFilter
{
public:
	SSAOFilter(const glm::uvec2& size);

};

#endif /*BAUASIAN_SSAO_FILTER_HPP */
