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

class bauasian::Bloom
{
public:
	Bloom(const glm::uvec2& size);

	void setSize(const glm::uvec2& size);
	void process(const Texture* const texture) const;
	const Texture* const getTexture() const;

private:
	glm::uvec2 m_size;
	unsigned m_down_sample = 2;
	unsigned m_down_sample_2 = 4;
	glm::uvec2 m_sampled_size;
	glm::uvec2 m_sampled_size_2;
	IntensityFilter m_intensity_filter;
	HorizontalGaussianBlur m_horizontal_blur;
	VerticalGaussianBlur m_vertical_blur;
	HorizontalGaussianBlur m_horizontal_blur_2;
	VerticalGaussianBlur m_vertical_blur_2;

};

#endif /* BAUASIAN_BLOOM_HPP */
