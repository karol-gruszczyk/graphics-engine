#include "context_size_interface.hpp"


using bauasian::ContextSizeInterface;

glm::uvec2 ContextSizeInterface::s_context_size;
std::list<ContextSizeInterface*> ContextSizeInterface::s_context_size_instances;

ContextSizeInterface::ContextSizeInterface()
{
	s_context_size_instances.push_back(this);
}

void ContextSizeInterface::setContextSize(const glm::uvec2& context_size)
{
	s_context_size = context_size;
	for (const auto& instance : s_context_size_instances)
		instance->updateContextSize();
}

const glm::uvec2& ContextSizeInterface::getContextSize()
{
	return s_context_size;
}
