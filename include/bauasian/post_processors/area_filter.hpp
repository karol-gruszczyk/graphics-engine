#ifndef BAUASIAN_ENGINE_AREA_FILTER_HPP
#define BAUASIAN_ENGINE_AREA_FILTER_HPP


#include "filter.hpp"


namespace bauasian
{
	class AreaFilter;
}

class bauasian::AreaFilter : public Filter
{
public:
	AreaFilter(const boost::filesystem::path& fragment_shader_path);

	virtual void setSize(const glm::uvec2& size) override;

private:
	GLint m_location_pixel_size;

};

#endif /* BAUASIAN_ENGINE_AREA_FILTER_HPP */
