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

	virtual void setContextSize(const unsigned& width, const unsigned& height) const override;
};


#endif /* BAUASIAN_ENGINE_AREA_FILTER_HPP */
