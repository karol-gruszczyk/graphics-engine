#include "intensity_filter.hpp"


using bauasian::IntensityFilter;

IntensityFilter::IntensityFilter(const glm::uvec2& size, GLenum storage)
		: Filter(size, "post_processing/intensity_fs.glsl", storage)
{}
