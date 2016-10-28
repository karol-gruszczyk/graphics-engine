#include "ssao.hpp"


using bauasian::SSAO;
using bauasian::Texture;

SSAO::SSAO(const glm::uvec2& size)
		: m_ssao_filter(size)
{}

void SSAO::setSize(const glm::uvec2& size)
{
	m_ssao_filter.setSize(size);
}

void SSAO::process(const Texture* const texture) const
{

}

void SSAO::processToScreen(const Texture* const texture) const
{

}

const Texture* const SSAO::getTexture() const
{
	return m_ssao_filter.getTexture();
}
