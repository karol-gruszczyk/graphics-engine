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
		OUTLINE, EXCESSIVE_OUTLINE, OUTLINE_HORIZONTAL, OUTLINE_VERTICAL,
		GRADIENT_DETECTION_HORIZONTAL, GRADIENT_DETECTION_VERTICAL,
		SHARPEN, INTENSE_SHARPEN,
		BOX_BLUR, GAUSSIAN_BLUR,
		EMBOSS,
		BOTTOM_SOBEL, TOP_SOBEL, LEFT_SOBEL, RIGHT_SOBEL
	};
	KernelFilter(const KernelFilterType& type);

protected:
	const glm::mat3 getKernelMatrix(const KernelFilterType& type);

};

#endif /* BAUASIAN_KERNEL_FILTER_HPP */