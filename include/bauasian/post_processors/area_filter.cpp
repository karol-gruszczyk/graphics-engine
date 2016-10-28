#include "area_filter.hpp"


using bauasian::AreaFilter;

AreaFilter::AreaFilter(const glm::uvec2& size, const boost::filesystem::path& fragment_shader_path)
		: Filter(size, fragment_shader_path)
{
	m_location_pixel_size = m_shader->getUniformLocation("pixel_size");
	m_shader->setUniform(m_location_pixel_size, 1.f / glm::vec2(m_color_texture->getSize()));
}

void AreaFilter::setSize(const glm::uvec2& size)
{
	Filter::setSize(size);
	m_shader->setUniform(m_location_pixel_size, 1.f / glm::vec2(m_color_texture->getSize()));
}
