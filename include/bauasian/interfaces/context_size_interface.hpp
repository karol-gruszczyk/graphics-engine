#ifndef BAUASIAN_CONTEXT_SIZE_INTERFACE_HPP
#define BAUASIAN_CONTEXT_SIZE_INTERFACE_HPP

#include <list>

#include <glm/glm.hpp>


namespace bauasian
{
	class ContextSizeInterface;
}

class bauasian::ContextSizeInterface
{
public:
	ContextSizeInterface();

	static void setContextSize(const glm::uvec2& context_size);

protected:
	virtual void updateContextSize() = 0;
	static const glm::uvec2& getContextSize();

private:
	static glm::uvec2 s_context_size;
	static std::list<ContextSizeInterface*> s_context_size_instances;

};

#endif /* BAUASIAN_CONTEXT_SIZE_INTERFACE_HPP */
