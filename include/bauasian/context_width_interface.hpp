#ifndef GRAPHICS_ENGINE_CONTEXT_WIDTH_INTERFACE_HPP
#define GRAPHICS_ENGINE_CONTEXT_WIDTH_INTERFACE_HPP


#include <list>
#include <glm/glm.hpp>


namespace bauasian
{
	class ContextWidthInterface;
}

class bauasian::ContextWidthInterface
{
public:
	ContextWidthInterface();

	static void setContextSize(const glm::uvec2& context_size);

protected:
	static glm::uvec2 s_context_size;
	static std::list<ContextWidthInterface*> s_context_size_instances;

	virtual void updateContextSize() = 0;
};

#endif /* GRAPHICS_ENGINE_CONTEXT_WIDTH_INTERFACE_HPP */
