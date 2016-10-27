#include "name_mixin.hpp"


using bauasian::NameMixin;

const std::string& NameMixin::getName() const
{
	return m_name;
}

void NameMixin::setName(const std::string& name)
{
	m_name = name;
}
