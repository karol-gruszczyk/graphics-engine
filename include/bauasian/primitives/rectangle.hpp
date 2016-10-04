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
	Rectangle(const glm::vec2& size, const glm::vec2& position = { 0.f, 0.f }, const glm::vec2& pivot = { 0.f, 0.f },
	          const GLfloat& rotation = 0.f, const glm::vec2& scale = { 1.f, 1.f });

protected:
	GLfloat m_length, m_width;
};

#endif /* BAUASIAN_RECTANGLE_HPP */
