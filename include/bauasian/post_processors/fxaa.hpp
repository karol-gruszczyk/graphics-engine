#ifndef BAUASIAN_FXAA_HPP
#define BAUASIAN_FXAA_HPP

#include "area_filter.hpp"


namespace bauasian
{
	class FXAA;
}

class bauasian::FXAA : public AreaFilter
{
public:
	enum Quality
	{
		VERY_LOW = 10, LOW = 12, MEDIUM = 15, HIGH = 20, VERY_HIGH = 25, ULTRA = 29, EXTREME = 39
	};

	FXAA(const Quality& quality = LOW);

	void setQuality(const Quality& quality);
	void setSubPixelRemoval(const float& sub_pixel_removal) const;
	void setEdgeThreshold(const float& edge_threshold) const;
	void setEdgeThresholdMin(const float& edge_threshold_min) const;

private:
	GLint m_location_subpix;
	GLint m_location_edge_threshold;
	GLint m_location_edge_threshold_min;

};

#endif /* BAUASIAN_FXAA_HPP */
