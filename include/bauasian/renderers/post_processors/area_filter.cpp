#include "area_filter.hpp"


using bauasian::AreaFilter;

AreaFilter::AreaFilter(const boost::filesystem::path& fragment_shader_path)
		: Filter(fragment_shader_path)
{
	initLocations();
}

AreaFilter::AreaFilter(Shader& fragment_shader)
		: Filter(fragment_shader)
{
	initLocations();
}

void AreaFilter::setSize(const glm::uvec2& size)
{
	Filter::setSize(size);
	m_shader->setUniform(m_location_pixel_size, 1.f / glm::vec2(m_color_texture->getSize()));
}

void AreaFilter::initLocations()
{
	m_location_pixel_size = m_shader->getUniformLocation("pixel_size");
}
