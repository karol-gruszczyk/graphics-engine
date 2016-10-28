#include "black_white_filter.hpp"


using bauasian::BlackWhiteFilter;

BlackWhiteFilter::BlackWhiteFilter(const glm::uvec2& size)
		: Filter(size, "post_processing/black_white_fs.glsl")
{}
