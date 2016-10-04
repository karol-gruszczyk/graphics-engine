#include "area_filter.hpp"


using bauasian::AreaFilter;

AreaFilter::AreaFilter(const boost::filesystem::path& fragment_shader_path)
		: Filter(fragment_shader_path)
{}

void AreaFilter::setContextSize(const unsigned& width, const unsigned& height) const
{
	Filter::setContextSize(width, height);
	m_shader->setUniformVector2("offset", { 1.f / width, 1.f / height });
}
