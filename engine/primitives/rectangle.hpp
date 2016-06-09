#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include "entities\entity_2d.hpp"


namespace engine
{
	class Rectangle;
}

class engine::Rectangle final : public Entity2D
{
public:
	Rectangle(glm::vec2 size, glm::vec2 position = { 0.f, 0.f }, glm::vec2 pivot = { 0.f, 0.f }, GLfloat rotation = 0.f, glm::vec2 scale = { 1.f, 1.f });
protected:
	GLfloat m_length, m_width;
};

#endif // RECTANGLE_HPP_
