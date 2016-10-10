#ifndef BAUASIAN_RECTANGLE_HPP
#define BAUASIAN_RECTANGLE_HPP

#include "abstract/entity_2d.hpp"


namespace bauasian
{
	class Rectangle;
}

class bauasian::Rectangle final : public Entity2D
{
public:
	Rectangle(const glm::vec2& size);

protected:
	GLfloat m_width, m_length;
};

#endif /* BAUASIAN_RECTANGLE_HPP */
