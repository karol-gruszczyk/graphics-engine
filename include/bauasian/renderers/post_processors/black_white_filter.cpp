#include "black_white_filter.hpp"


using bauasian::BlackWhiteFilter;

BlackWhiteFilter::BlackWhiteFilter(const glm::vec3& color_weights /* = { 0.2126, 0.7152, 0.0722 } */)
		: Filter("black_white_fs.glsl")
{
	const auto& location = m_shader->getUniformLocation("color_weight");
	m_shader->setUniform(location, color_weights);
}
