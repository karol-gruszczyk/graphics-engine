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
	AreaFilter(Shader& fragment_shader);

	virtual void setContextSize(const unsigned& width, const unsigned& height) override;

private:
	GLint m_location_pixel_size;

	void initLocations();

};

#endif /* BAUASIAN_ENGINE_AREA_FILTER_HPP */
