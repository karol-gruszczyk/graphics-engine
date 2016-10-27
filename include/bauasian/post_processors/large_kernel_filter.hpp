#ifndef BAUASIAN_LARGE_KERNEL_FILTER_HPP
#define BAUASIAN_LARGE_KERNEL_FILTER_HPP

#include "area_filter.hpp"


namespace bauasian
{
	class LargeKernelFilter;
}

class bauasian::LargeKernelFilter : public AreaFilter
{
public:
	enum LargeKernelFilterType
	{
		UNSHARP, SHARPEN, GAUSSIAN_BLUR
	};
	LargeKernelFilter(const LargeKernelFilterType& type);

private:
	const std::vector<float> getKernelMatrix(const LargeKernelFilterType& type);

};


#endif /* BAUASIAN_LARGE_KERNEL_FILTER_HPP */
