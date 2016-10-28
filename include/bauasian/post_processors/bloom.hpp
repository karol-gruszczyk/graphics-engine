#ifndef BAUASIAN_BLOOM_HPP
#define BAUASIAN_BLOOM_HPP

#include "post_processor.hpp"
#include "intensity_filter.hpp"
#include "horizontal_gaussian_blur.hpp"
#include "vertical_gaussian_blur.hpp"


namespace bauasian
{
	class Bloom;
}

class bauasian::Bloom : public PostProcessor
{
public:
	Bloom(const glm::uvec2& size, unsigned down_sample = 2);

	virtual void setSize(const glm::uvec2& size);
	virtual void process(const Texture* const texture) const;
	virtual void processToScreen(const Texture* const texture) const;
	virtual const Texture* const getTexture() const;

private:
	glm::uvec2 m_size;
	unsigned m_down_sample;
	glm::uvec2 m_sampled_size;
	IntensityFilter m_intensity_filter;
	HorizontalGaussianBlur m_horizontal_blur;
	VerticalGaussianBlur m_vertical_blur;

};

#endif /* BAUASIAN_BLOOM_HPP */
