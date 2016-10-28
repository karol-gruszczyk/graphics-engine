#include "vertical_gaussian_blur.hpp"


using bauasian::VerticalGaussianBlur;

VerticalGaussianBlur::VerticalGaussianBlur(const glm::uvec2& size)
		: AreaFilter(size, "post_processing/gaussian_blur/vertical_fs.glsl")
{}
