#include "hdr.hpp"


using bauasian::HDR;

HDR::HDR(const glm::uvec2& size, const float& exposure, const float& gamma)
		: Filter(size, "post_processing/hdr_fs.glsl", GL_RGBA)
{
	m_location_exposure = m_shader->getUniformLocation("exposure");
	m_location_gamma = m_shader->getUniformLocation("gamma");
	m_shader->setUniform(m_shader->getUniformLocation("screen_texture"), 0);
	m_shader->setUniform(m_shader->getUniformLocation("bloom_texture"), 1);
	setExposure(exposure);
	setGamma(gamma);
}

void HDR::process(const Texture* const color_texture, const Texture* const bloom_texture) const
{
	bloom_texture->bind(1);
	Filter::process(color_texture);
}

void HDR::processToScreen(const Texture* const color_texture, const Texture* const bloom_texture) const
{
	bloom_texture->bind(1);
	Filter::processToScreen(color_texture);
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