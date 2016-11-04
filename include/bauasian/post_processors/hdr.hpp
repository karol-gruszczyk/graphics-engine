#ifndef BAUASIAN_HDR_HPP
#define BAUASIAN_HDR_HPP

#include "filter.hpp"


namespace bauasian
{
	class HDR;
}

class bauasian::HDR : public Filter
{
public:
	HDR(const glm::uvec2& size, float exposure = 1.f, float gamma = 2.2f);

	float getExposure() const;
	void setExposure(float exposure);
	float getGamma() const;
	void setGamma(float gamma);

private:
	float m_exposure, m_gamma;

	GLint m_location_exposure, m_location_gamma;

};


#endif /* BAUASIAN_HDR_HPP */
