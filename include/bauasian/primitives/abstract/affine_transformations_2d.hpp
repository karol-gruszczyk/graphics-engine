#ifndef BAUASIAN_AFFINE_TRANSFORMATIONS_2D_HPP
#define BAUASIAN_AFFINE_TRANSFORMATIONS_2D_HPP

#include <glm/glm.hpp>


namespace bauasian
{
	class AffineTransformations2D;
}

class bauasian::AffineTransformations2D
{
public:
	virtual const glm::vec2& getPosition() const
	{ return m_position; }
	virtual void setPosition(const glm::vec2& position);
	virtual void translate(const glm::vec2& position);

	virtual float getRotation() const
	{ return m_rotation; }
	virtual void setRotation(float rotation);
	virtual void rotate(float rotation);

	virtual const glm::vec2& getScale() const
	{ return m_scale; }
	virtual void setScale(const glm::vec2& scale);

	virtual const glm::vec2& getPivot() const
	{ return m_pivot; }
	virtual void setPivot(const glm::vec2& pivot);

	virtual const glm::mat4& getModelMatrix() const
	{ return m_model_matrix; }

protected:
	glm::vec2 m_position = { 0.f, 0.f };
	float m_rotation = 0.f;
	glm::vec2 m_scale = { 1.f, 1.f };
	glm::vec2 m_pivot = { 0.f, 0.f };

	glm::mat4 m_model_matrix;

};

#endif /* BAUASIAN_AFFINE_TRANSFORMATIONS_2D_HPP */
