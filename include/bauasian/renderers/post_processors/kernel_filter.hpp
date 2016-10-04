#ifndef BAUASIAN_KERNEL_FILTER_HPP
#define BAUASIAN_KERNEL_FILTER_HPP


#include "area_filter.hpp"


namespace bauasian
{
	class KernelFilter;
}

class bauasian::KernelFilter : public AreaFilter
{
public:
	enum KernelFilterType
	{
		EDGE_DETECTION, SHARPEN, BOX_BLUR, GAUSSIAN_BLUR
	};
	KernelFilter(const KernelFilterType& type);

protected:
	const std::tuple<GLfloat, glm::mat3> getKernel(const KernelFilterType& type);

};

#endif /* BAUASIAN_KERNEL_FILTER_HPP */
