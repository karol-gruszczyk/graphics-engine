#include "context_width_interface.hpp"


using engine::ContextWidthInterface;

glm::uvec2 ContextWidthInterface::s_context_size;
std::list<ContextWidthInterface*> ContextWidthInterface::s_context_size_instances;

ContextWidthInterface::ContextWidthInterface()
{
	s_context_size_instances.push_back(this);
}

void ContextWidthInterface::setContextSize(const glm::uvec2& context_size)
{
	s_context_size = context_size;
	for (const auto& instance : s_context_size_instances)
		instance->updateContextSize();
}
