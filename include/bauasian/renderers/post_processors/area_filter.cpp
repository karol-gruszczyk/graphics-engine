#include "area_filter.hpp"


using bauasian::AreaFilter;

AreaFilter::AreaFilter(const boost::filesystem::path& fragment_shader_path)
		: Filter(fragment_shader_path)
{
	m_location_pixel_size = m_shader->getUniformLocation("pixel_size");
}

void AreaFilter::setContextSize(const unsigned& width, const unsigned& height) const
{
	Filter::setContextSize(width, height);
	m_shader->setUniform(m_location_pixel_size, { 1.f / width, 1.f / height });
}
