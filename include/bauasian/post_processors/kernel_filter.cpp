#include "kernel_filter.hpp"


using bauasian::KernelFilter;

KernelFilter::KernelFilter(const glm::uvec2& size, const KernelFilter::KernelFilterType& type)
		: AreaFilter(size, "post_processing/kernel_fs.glsl")
{
	const auto& location = m_shader->getUniformLocation("kernel_matrix");
	m_shader->setUniform(location, getKernelMatrix(type));
}

const glm::mat3 KernelFilter::getKernelMatrix(const KernelFilter::KernelFilterType& type)
{
	switch (type)
	{
		case OUTLINE:
			return glm::mat3(-1, -1, -1,
			                 -1, 8, -1,
			                 -1, -1, -1);
		case EXCESSIVE_OUTLINE:
			return glm::mat3(1, 1, 1,
			                 1, -7, 1,
			                 1, 1, 1);
		case OUTLINE_HORIZONTAL:
			return glm::mat3(0, 0, 0,
			                 -1, 2, -1,
			                 0, 0, 0);
		case OUTLINE_VERTICAL:
			return glm::mat3(0, -1, 0,
			                 0, 2, 0,
			                 0, -1, 0);
		case GRADIENT_DETECTION_HORIZONTAL:
			return glm::mat3(-1, -1, -1,
			                 0, 0, 0,
			                 1, 1, 1);
		case GRADIENT_DETECTION_VERTICAL:
			return glm::mat3(-1, 0, 1,
			                 -1, 0, 1,
			                 -1, 0, 1);
		case SHARPEN:
			return glm::mat3(0, -1, 0,
			                 -1, 5, -1,
			                 0, -1, 0);
		case INTENSE_SHARPEN:
			return glm::mat3(-1, -1, -1,
			                 -1, 9, -1,
			                 -1, -1, -1);
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
