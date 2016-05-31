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
	Entity2D(glm::vec2 position, GLfloat rotation = 0.f, glm::vec2 scale = { 1.f, 1.f }, glm::vec2 pivot = { 0.f, 0.f });

	void translate(glm::vec2 position);
	void setPosition(glm::vec2 position);
	glm::vec2 getPosition();
	void rotate(GLfloat rotation);
	void setRotation(GLfloat rotation);
	GLfloat getRotation();
	void setScale(glm::vec2 scale);
	glm::vec2 getScale();
	void setPivot(glm::vec2 pivot);
	glm::vec2 getPivot();
protected:
	glm::vec2 m_position;
	GLfloat m_rotation;
	glm::vec2 m_scale;
	glm::vec2 m_pivot;
};

#endif /* ENTITY_2D_H_ */
