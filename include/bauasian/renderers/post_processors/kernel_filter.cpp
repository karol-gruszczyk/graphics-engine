#include "kernel_filter.hpp"


using bauasian::KernelFilter;

KernelFilter::KernelFilter(const bauasian::KernelFilter::KernelFilterType& type)
		: AreaFilter("kernel_fs.glsl")
{
	m_shader->setUniformMatrix3("kernel_matrix", getKernelMatrix(type));
}

const glm::mat3 KernelFilter::getKernelMatrix(const KernelFilter::KernelFilterType& type)
{
	switch (type)
	{
		case OUTLINE:
			return glm::mat3(-1, -1, -1,
			                 -1, 8, -1,
			                 -1, -1, -1);
		case SHARPEN:
			return glm::mat3(0, -1, 0,
			                 -1, 5, -1,
			                 0, -1, 0);
		case BOX_BLUR:
			return glm::mat3(1, 1, 1,
			                 1, 1, 1,
			                 1, 1, 1) / 9.f;
		case GAUSSIAN_BLUR:
			return glm::mat3(1, 2, 1,
			                 2, 4, 2,
			                 1, 2, 1) / 16.f;
		case EMBOSS:
			return glm::mat3(-2, -1, 0,
			                 -1, 1, 1,
			                 0, 1, 2);
		case BOTTOM_SOBEL:
			return glm::mat3(-1, -2, -1,
			                 0, 0, 0,
			                 1, 2, 1);
		case TOP_SOBEL:
			return glm::mat3(1, 2, 1,
			                 0, 0, 0,
			                 -1, -2, -1);
		case LEFT_SOBEL:
			return glm::mat3(1, 0, -1,
			                 2, 0, -2,
			                 1, 0, -1);
		case RIGHT_SOBEL:
			return glm::mat3(-1, 0, 1,
			                 -2, 0, 2,
			                 01, 0, 1);
	}
	throw new std::invalid_argument("type");
}
