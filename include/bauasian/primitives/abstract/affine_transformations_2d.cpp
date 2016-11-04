#include "affine_transformations_2d.hpp"

#include <glm/gtc/matrix_transform.hpp>


using bauasian::AffineTransformations2D;

const glm::vec2& AffineTransformations2D::getPosition() const
{
	return m_position;
}

void AffineTransformations2D::setPosition(const glm::vec2& position)
{
	translate(position - m_position);
}

void AffineTransformations2D::translate(const glm::vec2& position)
{
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(position, 0.f));
	m_position += position;
}

float AffineTransformations2D::getRotation() const
{
	return m_rotation;
}

void AffineTransformations2D::setRotation(float rotation)
{
	rotate(rotation - m_rotation);
}

void AffineTransformations2D::rotate(float rotation)
{
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(m_pivot, 0.f));
	m_model_matrix = glm::rotate(m_model_matrix, rotation, { 0.f, 0.f, 1.f });
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(-m_pivot, 0.f));
	m_rotation += rotation;
}

const glm::vec2& AffineTransformations2D::getScale() const
{
	return m_scale;
}

void AffineTransformations2D::setScale(const glm::vec2& scale)
{
	m_model_matrix = glm::translate(glm::mat4(), glm::vec3(m_position, 0.f));
	m_model_matrix = glm::scale(m_model_matrix, glm::vec3(scale.x, scale.y, 1.f));
	m_model_matrix = glm::rotate(m_model_matrix, m_rotation, { 0.f, 0.f, 1.f });
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(-m_pivot, 0.f));
	m_scale = scale;
}

const glm::vec2& AffineTransformations2D::getPivot() const
{
	return m_pivot;
}

void AffineTransformations2D::setPivot(const glm::vec2& pivot)
{
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(m_pivot - pivot, 0.f));
	m_pivot = pivot;
}

const glm::mat4& AffineTransformations2D::getModelMatrix() const
{
	return m_model_matrix;
}
