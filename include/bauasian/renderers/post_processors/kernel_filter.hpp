#ifndef GRAPHICS_ENGINE_KERNEL_FILTER_HPP
#define GRAPHICS_ENGINE_KERNEL_FILTER_HPP


#include "post_processor.hpp"


namespace bauasian
{
	class KernelFilter;
}

class bauasian::KernelFilter : public PostProcessor
{
public:
	enum KernelFilterType
	{
		EDGE_DETECTION, SHARPEN
	};
	KernelFilter(const KernelFilterType& type);
	virtual void setContextSize(const unsigned& width, const unsigned& height) const override;

protected:
	const std::tuple<GLfloat, glm::mat3> getKernel(const KernelFilterType& type);

};

#endif /* GRAPHICS_ENGINE_KERNEL_FILTER_HPP */
