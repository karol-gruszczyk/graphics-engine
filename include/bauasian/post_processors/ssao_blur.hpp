#ifndef BAUASIAN_SSAO_BLUR_HPP
#define BAUASIAN_SSAO_BLUR_HPP

#include "area_filter.hpp"


namespace bauasian
{
	class SSAOBlur;
}

class bauasian::SSAOBlur : public AreaFilter
{
public:
	SSAOBlur(const glm::uvec2& size);

};

#endif /* BAUASIAN_SSAO_BLUR_HPP */
