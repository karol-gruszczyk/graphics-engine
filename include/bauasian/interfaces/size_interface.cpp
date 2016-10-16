#include "size_interface.hpp"


using bauasian::SizeInterface;

SizeInterface::SizeInterface(const glm::uvec2& size)
		: m_size(size)
{}

const glm::uvec2& SizeInterface::getSize() const
{
	return m_size;
}

void SizeInterface::setSize(const glm::uvec2& size)
{
	m_size = size;
}
