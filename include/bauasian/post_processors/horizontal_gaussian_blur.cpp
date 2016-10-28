#include "horizontal_gaussian_blur.hpp"


using bauasian::HorizontalGaussianBlur;

HorizontalGaussianBlur::HorizontalGaussianBlur(const glm::uvec2& size)
		: AreaFilter(size, "post_processing/gaussian_blur/horizontal_fs.glsl")
{}
