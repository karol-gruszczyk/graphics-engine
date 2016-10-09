#ifndef BAUASIAN_NAME_INTERFACE_HPP
#define BAUASIAN_NAME_INTERFACE_HPP

#include <string>


namespace bauasian
{
	class NameInterface;
}

class bauasian::NameInterface
{
public:
	const std::string& getName() const;
	void setName(const std::string& name);

protected:
	std::string m_name;
};

#endif /* BAUASIAN_NAME_INTERFACE_HPP */
