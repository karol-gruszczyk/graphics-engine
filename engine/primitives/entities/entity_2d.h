#ifndef ENTITY_2D_H_
#define ENTITY_2D_H_

#include "entity.h"


namespace engine
{
	class Entity2D;
}

class engine::Entity2D abstract : public Entity
{
public:
	Entity2D(glm::vec2 position, GLfloat rotation = 0.f, GLfloat scale = 1.f, glm::vec2 pivot = { 0.f, 0.f });

	void rotate(GLfloat angle);
	void setRotation(GLfloat angle);
	GLfloat getRotation();
	void translate(glm::vec2 position);
	void setPosition(glm::vec2 position);
	glm::vec2 getPosition();
	void setScale(GLfloat scale);
	GLfloat getScale();
	void setPivot(glm::vec2 pivot);
	glm::vec2 getPivot();
protected:
	glm::vec2 m_position;
	GLfloat m_rotation;
	GLfloat m_scale;
	glm::vec2 m_pivot;
};

#endif /* ENTITY_2D_H_ */
