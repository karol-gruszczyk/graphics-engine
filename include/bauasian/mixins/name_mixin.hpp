#ifndef BAUASIAN_NAME_MIXIN_HPP
#define BAUASIAN_NAME_MIXIN_HPP

#include <string>


namespace bauasian
{
	class NameMixin;
}

class bauasian::NameMixin
{
public:
	const std::string& getName() const
	{ return m_name; }
	void setName(const std::string& name)
	{ m_name = name; }

protected:
	std::string m_name;

};

#endif /* BAUASIAN_NAME_MIXIN_HPP */
