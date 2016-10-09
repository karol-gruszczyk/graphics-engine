#include "name_interface.hpp"


using bauasian::NameInterface;

const std::string& NameInterface::getName() const
{
	return m_name;
}

void NameInterface::setName(const std::string& name)
{
	m_name = name;
}
