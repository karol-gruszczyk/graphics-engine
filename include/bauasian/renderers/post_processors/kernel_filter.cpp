#include "kernel_filter.hpp"


using bauasian::KernelFilter;

KernelFilter::KernelFilter(const bauasian::KernelFilter::KernelFilterType& type)
		: PostProcessor("post_processing/kernel_fs.glsl")
{
	auto kernel = getKernel(type);
	m_shader->setUniformMatrix3("kernel_matrix", std::get<1>(kernel));
	m_shader->setUniformFloat("kernel_multiplier", std::get<0>(kernel));
}

const std::tuple<GLfloat, glm::mat3> KernelFilter::getKernel(const KernelFilter::KernelFilterType& type)
{
	switch (type)
	{
		case EDGE_DETECTION:
			return std::make_tuple(1.f, glm::mat3({
					                                      -1, -1, -1,
					                                      -1, 8, -1,
					                                      -1, -1, -1,
			                                      }));
		case SHARPEN:
			return std::make_tuple(1.f, glm::mat3({
					                                      0, -1, 0,
					                                      -1, 5, -1,
					                                      0, -1, 0,
			                                      }));
	}
	throw new std::invalid_argument("type");
}

void KernelFilter::setContextSize(const unsigned& width, const unsigned& height) const
{
	PostProcessor::setContextSize(width, height);
	m_shader->setUniformVector2("offset", { 1.f / width, 1.f / height });
}
