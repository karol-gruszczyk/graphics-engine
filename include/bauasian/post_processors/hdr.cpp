#include "hdr.hpp"


using bauasian::HDR;

HDR::HDR(const glm::uvec2& size, const float& exposure, const float& gamma)
		: Filter(size, "post_processing/hdr_fs.glsl", GL_RGBA16F)
{
	m_location_exposure = m_shader->getUniformLocation("exposure");
	m_location_gamma = m_shader->getUniformLocation("gamma");
	setExposure(exposure);
	setGamma(gamma);
}

const float& HDR::getExposure() const
{
	return m_exposure;
}

void HDR::setExposure(const float& exposure)
{
	m_exposure = exposure;
	m_shader->setUniform(m_location_exposure, m_exposure);
}

const float& HDR::getGamma() const
{
	return m_gamma;
}

void HDR::setGamma(const float& gamma)
{
	m_gamma = gamma;
	m_shader->setUniform(m_location_gamma, m_gamma);
}
