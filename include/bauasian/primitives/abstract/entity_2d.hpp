#ifndef BAUASIAN_ENTITY_2D_HPP
#define BAUASIAN_ENTITY_2D_HPP

#include "entity.hpp"
#include "bauasian/materials/basic_material.hpp"


namespace bauasian
{
	class Entity2D;
}

class bauasian::Entity2D : public Entity
{
public:
	virtual void translate(const glm::vec2& position);
	virtual void setPosition(const glm::vec2& position);
	virtual const glm::vec2& getPosition() const;
	virtual void rotate(const GLfloat& rotation);
	virtual void setRotation(const GLfloat& rotation);
	virtual GLfloat getRotation() const;
	virtual void setScale(const glm::vec2& scale);
	virtual const glm::vec2& getScale() const;
	virtual void setPivot(const glm::vec2& pivot);
	virtual const glm::vec2& getPivot() const;

	virtual void setMaterial(BasicMaterial* material);
	virtual void render() const override;
protected:
	BasicMaterial* m_material = nullptr;

	glm::vec2 m_position = { 0.f, 0.f };
	GLfloat m_rotation = 0.f;
	glm::vec2 m_scale = { 1.f, 1.f };
	glm::vec2 m_pivot = { 0.f, 0.f };
};

#endif /* BAUASIAN_ENTITY_2D_HPP */
