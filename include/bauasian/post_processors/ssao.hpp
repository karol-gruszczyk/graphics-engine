#ifndef BAUASIAN_SSAO_HPP
#define BAUASIAN_SSAO_HPP

#include "ssao_filter.hpp"


namespace bauasian
{
	class SSAO;
}

class bauasian::SSAO : public PostProcessor
{
public:
	SSAO(const glm::uvec2& size);

	virtual void setSize(const glm::uvec2& size);
	virtual void process(const Texture* const texture) const;
	virtual void processToScreen(const Texture* const texture) const;
	virtual const Texture* const getTexture() const;

private:
	SSAOFilter m_ssao_filter;

};

#endif /* BAUASIAN_SSAO_HPP */
