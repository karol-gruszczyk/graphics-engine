#include "bloom.hpp"


using bauasian::Bloom;
using bauasian::Texture;

Bloom::Bloom(const glm::uvec2& size)
		: m_size(size), m_sampled_size(m_size / m_down_sample), m_sampled_size_2(m_size / m_down_sample_2),
		  m_intensity_filter(m_sampled_size, GL_RGB16F),
		  m_horizontal_blur(m_sampled_size, GL_RGB16F), m_vertical_blur(m_sampled_size, GL_RGB16F),
		  m_horizontal_blur_2(m_sampled_size_2, GL_RGB16F), m_vertical_blur_2(m_sampled_size_2, GL_RGB16F)
{}

void Bloom::setSize(const glm::uvec2& size)
{
	m_size = size;
	m_sampled_size = m_size / m_down_sample;
	m_intensity_filter.setSize(m_sampled_size);
	m_horizontal_blur.setSize(m_sampled_size);
	m_vertical_blur.setSize(m_sampled_size);
	m_horizontal_blur_2.setSize(m_sampled_size_2);
	m_vertical_blur_2.setSize(m_sampled_size_2);
}

void Bloom::process(const Texture* const texture) const
{
	glViewport(0, 0, m_sampled_size.x, m_sampled_size.y);
	m_intensity_filter.process(texture);
	m_horizontal_blur.process(m_intensity_filter.getTexture());
	m_vertical_blur.process(m_horizontal_blur.getTexture());
	glViewport(0, 0, m_sampled_size_2.x, m_sampled_size_2.y);
	m_horizontal_blur_2.process(m_vertical_blur.getTexture());
	m_vertical_blur_2.process(m_horizontal_blur_2.getTexture());
	glViewport(0, 0, m_size.x, m_size.y);
}

void Bloom::processToScreen(const Texture* const texture) const
{
	throw std::runtime_error("Bloom effect is designed to work with HDR");
}

const Texture* const Bloom::getTexture() const
{
	return m_vertical_blur_2.getTexture();
}
