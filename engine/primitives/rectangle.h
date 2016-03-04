#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "entities\entity2d.h"

namespace engine
{
	class Rectangle;
}

class engine::Rectangle final : public engine::Entity2D
{
public:
	Rectangle() {}
	Rectangle(GLfloat width, GLfloat length);
	void initialize(GLfloat width, GLfloat length);
	void render() override;
protected:
	GLfloat m_length, m_width;
};

#endif // RECTANGLE_H_
