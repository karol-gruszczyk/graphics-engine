#include "size_mixin.hpp"


using bauasian::SizeMixin;

const glm::uvec2& SizeMixin::getSize() const
{
	return m_size;
}

void SizeMixin::setSize(const glm::uvec2& size)
{
	m_size = size;
}
