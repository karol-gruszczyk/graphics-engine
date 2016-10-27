#include "context_size_observer.hpp"


using bauasian::ContextSizeObserver;

glm::uvec2 ContextSizeObserver::s_context_size;
std::list<ContextSizeObserver*> ContextSizeObserver::s_context_size_instances;

ContextSizeObserver::ContextSizeObserver()
{
	s_context_size_instances.push_back(this);
}

void ContextSizeObserver::setContextSize(const glm::uvec2& context_size)
{
	s_context_size = context_size;
	for (const auto& instance : s_context_size_instances)
		instance->updateContextSize();
}

const glm::uvec2& ContextSizeObserver::getContextSize()
{
	return s_context_size;
}
