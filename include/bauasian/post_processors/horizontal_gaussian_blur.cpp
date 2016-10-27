#include "horizontal_gaussian_blur.hpp"


using bauasian::HorizontalGaussianBlur;

HorizontalGaussianBlur::HorizontalGaussianBlur()
		: AreaFilter("post_processing/gaussian_blur/horizontal_fs.glsl")
{}
