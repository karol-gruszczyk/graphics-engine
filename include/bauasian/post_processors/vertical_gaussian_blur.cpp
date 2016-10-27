#include "vertical_gaussian_blur.hpp"


using bauasian::VerticalGaussianBlur;

VerticalGaussianBlur::VerticalGaussianBlur()
		: AreaFilter("post_processing/gaussian_blur/vertical_fs.glsl")
{}
