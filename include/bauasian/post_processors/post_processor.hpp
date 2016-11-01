#ifndef BAUASIAN_POST_PROCESSOR_HPP
#define BAUASIAN_POST_PROCESSOR_HPP

#include "bauasian/textures/texture.hpp"
#include "bauasian/glsl/bindings.glsl"


namespace bauasian
{
	class PostProcessor;
}

class bauasian::PostProcessor
{
public:
	virtual ~PostProcessor() {}

	virtual void setSize(const glm::uvec2& size) = 0;
	virtual void process(const unsigned short& out_binding = POST_PROCESSING_COLOR_TEXTURE) const = 0;
	virtual void processToScreen() const = 0;

};

#endif /* BAUASIAN_POST_PROCESSOR_HPP */
