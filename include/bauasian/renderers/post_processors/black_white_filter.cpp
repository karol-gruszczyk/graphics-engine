#include "black_white_filter.hpp"


using bauasian::BlackWhiteFilter;

BlackWhiteFilter::BlackWhiteFilter(const glm::vec3& color_weights /* = { 0.2126, 0.7152, 0.0722 } */)
		: Filter("black_white_fs.glsl")
{
	m_shader->setUniformVector3("color_weight", color_weights);
}
