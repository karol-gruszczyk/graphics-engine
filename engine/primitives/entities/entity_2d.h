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

	void setRotation(GLfloat angle);
	GLfloat getRotation();
	void rotate(GLfloat angle);
	void setPosition(glm::vec2 position);
	glm::vec2 getPosition();
	void setRotationRad(GLfloat angle);
	GLfloat getRotationRad();
	void rotateRad(GLfloat angle);
	void translate(glm::vec2 position);
	void setScale(GLfloat scale);
	GLfloat getScale();
	void setPivot(glm::vec2 pivot);
	glm::vec2 getPivot();
protected:
	glm::vec2 m_position;
	GLfloat m_rotation = 0.f;
	GLfloat m_rotation_rad = 0.f;
	GLfloat m_scale = 1.f;
	glm::vec2 m_pivot;

	void updatePivotMatrix();
	void updateTranslationMatrix();
	void updateRotationMatrix();
	void updateScaleMatrix();
};

#endif /* ENTITY_2D_H_ */
