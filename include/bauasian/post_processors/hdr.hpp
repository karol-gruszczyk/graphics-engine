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
	HDR(const glm::uvec2& size, const float& exposure = 1.f, const float& gamma = 2.2f);

	const float& getExposure() const;
	void setExposure(const float& exposure);
	const float& getGamma() const;
	void setGamma(const float& gamma);

private:
	float m_exposure, m_gamma;

	GLint m_location_exposure, m_location_gamma;

};


#endif /* BAUASIAN_HDR_HPP */
