#ifndef BAUASIAN_SIZE_MIXIN_HPP
#define BAUASIAN_SIZE_MIXIN_HPP

#include <glm/glm.hpp>


namespace bauasian
{
	class SizeMixin;
}


class bauasian::SizeMixin
{
public:
	SizeMixin(const glm::uvec2& size);

	virtual const glm::uvec2& getSize() const;
	virtual void setSize(const glm::uvec2& size);

protected:
	glm::uvec2 m_size;

};

#endif /* BAUASIAN_SIZE_MIXIN_HPP */
