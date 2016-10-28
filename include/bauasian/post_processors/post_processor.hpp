#ifndef BAUASIAN_POST_PROCESSOR_HPP
#define BAUASIAN_POST_PROCESSOR_HPP

#include "bauasian/materials/texture.hpp"


namespace bauasian
{
	class PostProcessor;
}

class bauasian::PostProcessor
{
public:
	virtual ~PostProcessor() {}

	virtual void setSize(const glm::uvec2& size) = 0;
	virtual void process(const Texture* const texture) const = 0;
	virtual void processToScreen(const Texture* const texture) const = 0;
	virtual const Texture* const getTexture() const = 0;

};

#endif /* BAUASIAN_POST_PROCESSOR_HPP */
