#ifndef ENTITY_2D_HPP_
#define ENTITY_2D_HPP_

#include "entity.hpp"
#include "../../materials/material.hpp"


namespace engine
{
	class Entity2D;
}

class engine::Entity2D : public Entity
{
public:
	Entity2D(const glm::vec2& position, const GLfloat& rotation = 0.f, const glm::vec2& scale = { 1.f, 1.f }, const glm::vec2& pivot = { 0.f, 0.f });

	void translate(const glm::vec2& position);
	void setPosition(const glm::vec2& position);
	const glm::vec2& getPosition() const;
	void rotate(const GLfloat& rotation);
	void setRotation(const GLfloat& rotation);
	GLfloat getRotation() const;
	void setScale(const glm::vec2& scale);
	const glm::vec2& getScale() const;
	void setPivot(const glm::vec2& pivot);
	const glm::vec2& getPivot() const;
protected:
	glm::vec2 m_position;
	GLfloat m_rotation;
	glm::vec2 m_scale;
	glm::vec2 m_pivot;
};

#endif /* ENTITY_2D_HPP_ */
