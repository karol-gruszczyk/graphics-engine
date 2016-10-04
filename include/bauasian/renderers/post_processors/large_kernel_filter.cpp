#include "large_kernel_filter.hpp"


using bauasian::LargeKernelFilter;

LargeKernelFilter::LargeKernelFilter(const bauasian::LargeKernelFilter::LargeKernelFilterType& type)
		: AreaFilter("large_kernel_fs.glsl")
{
	m_shader->setUniformFloatVector("kernel_matrix", &getKernelMatrix(type)[0], 25);
}

const std::vector<float> LargeKernelFilter::getKernelMatrix(const LargeKernelFilter::LargeKernelFilterType& type)
{
	std::vector<float> result_matrix(25);
	float matrix_multiplier(1.f);
	switch (type)
	{
		case UNSHARP:
			result_matrix = { 1, 4, 6, 4, 1,
			                  4, 16, 24, 16, 4,
			                  6, 24, -476, 24, 6,
			                  4, 16, 24, 16, 4,
			                  1, 4, 6, 4, 1 };
			matrix_multiplier = -1.f / 256.f;
			break;
		case SHARPEN:
			result_matrix = { -1, -1, -1, -1, -1,
			                  -1, 2, 2, 2, -1,
			                  -1, 2, 8, 2, -1,
			                  -1, 2, 2, 2, -1,
			                  -1, -1, -1, -1, -1 };
			matrix_multiplier = 1.f / 8.f;
			break;
		case GAUSSIAN_BLUR:
			result_matrix = { 1, 4, 7, 4, 1,
			         4, 16, 26, 16, 4,
			         7, 26, 41, 26, 7,
			         4, 16, 26, 16, 4,
			         1, 4, 7, 4, 1 };
			matrix_multiplier = 1.f / 273.f;
			break;
		default:
			throw new std::invalid_argument("type");
	}
	if (matrix_multiplier != 1.f)
		for (auto& elem : result_matrix)
			elem *= matrix_multiplier;
	return result_matrix;
}
