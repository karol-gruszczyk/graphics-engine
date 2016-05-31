#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "entities\entity_2d.h"


namespace engine
{
	class Rectangle;
}

class engine::Rectangle final : public Entity2D
{
public:
	Rectangle(glm::vec2 size, glm::vec2 position = { 0.f, 0.f }, glm::vec2 pivot = { 0.f, 0.f }, GLfloat rotation = 0.f, GLfloat scale = 1.f);

	void render() override;
protected:
	GLfloat m_length, m_width;
};

#endif // RECTANGLE_H_
