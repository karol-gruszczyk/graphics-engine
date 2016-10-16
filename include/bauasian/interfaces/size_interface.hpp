#ifndef BAUASIAN_SIZE_INTERFACE_HPP
#define BAUASIAN_SIZE_INTERFACE_HPP

#include <glm/glm.hpp>


namespace bauasian
{
	class SizeInterface;
}


class bauasian::SizeInterface
{
public:
	SizeInterface(const glm::uvec2& size);

	virtual const glm::uvec2& getSize() const;
	virtual void setSize(const glm::uvec2& size);

protected:
	glm::uvec2 m_size;

};

#endif /* BAUASIAN_SIZE_INTERFACE_HPP */
