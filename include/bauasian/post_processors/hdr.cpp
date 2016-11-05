#include "hdr.hpp"


using bauasian::HDR;

HDR::HDR(const glm::uvec2& size, float exposure, float gamma)
		: Filter(size, "post_processing/hdr_fs.glsl", GL_RGBA)
{
	m_location_exposure = m_shader->getUniformLocation("exposure");
	m_location_gamma = m_shader->getUniformLocation("gamma");
	m_shader->setUniform(m_shader->getUniformLocation("screen_texture"), 0);
	m_shader->setUniform(m_shader->getUniformLocation("bloom_texture"), 1);
	setExposure(exposure);
	setGamma(gamma);
}

void HDR::setExposure(float exposure)
{
	m_exposure = exposure;
	m_shader->setUniform(m_location_exposure, m_exposure);
}

void HDR::setGamma(float gamma)
{
	m_gamma = gamma;
	m_shader->setUniform(m_location_gamma, m_gamma);
}