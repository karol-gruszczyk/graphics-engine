#include "affine_transformations.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>


using bauasian::AffineTransformations;


const glm::vec3& AffineTransformations::getPosition() const
{
	return m_position;
}

void AffineTransformations::setPosition(const glm::vec3& position)
{
	translate(position - m_position);
}

void AffineTransformations::translate(const glm::vec3& position)
{
	m_model_matrix = glm::translate(m_model_matrix, position);
	m_position += position;
}

const glm::vec3& AffineTransformations::getRotation() const
{
	return m_rotation;
}

void AffineTransformations::setRotation(const glm::vec3& rotation)
{
	rotate(rotation - m_rotation);
}

void AffineTransformations::rotate(const glm::vec3& rotation)
{
	m_model_matrix = glm::translate(m_model_matrix, m_pivot);
	m_model_matrix = glm::rotate(m_model_matrix, rotation.x, { 1.f, 0.f, 0.f });
	m_model_matrix = glm::rotate(m_model_matrix, rotation.y, { 0.f, 1.f, 0.f });
	m_model_matrix = glm::rotate(m_model_matrix, rotation.z, { 0.f, 0.f, 1.f });
	m_model_matrix = glm::translate(m_model_matrix, -m_pivot);
	m_rotation += rotation;
}

const glm::vec3& AffineTransformations::getScale() const
{
	return m_scale;
}

void AffineTransformations::setScale(const glm::vec3& scale)
{
	m_model_matrix = glm::translate(glm::mat4(), m_position);
	m_model_matrix = glm::scale(m_model_matrix, scale);
	m_model_matrix = glm::rotate(m_model_matrix, m_rotation.x, { 1.f, 0.f, 0.f });
	m_model_matrix = glm::rotate(m_model_matrix, m_rotation.y, { 0.f, 1.f, 0.f });
	m_model_matrix = glm::rotate(m_model_matrix, m_rotation.z, { 0.f, 0.f, 1.f });
	m_model_matrix = glm::translate(m_model_matrix, -m_pivot);
	m_scale = scale;
}

const glm::vec3& AffineTransformations::getPivot() const
{
	return m_pivot;
}

void AffineTransformations::setPivot(const glm::vec3& pivot)
{
	m_model_matrix = glm::translate(m_model_matrix, m_pivot - pivot);
	m_pivot = pivot;
}

const glm::mat4& AffineTransformations::getModelMatrix() const
{
	return m_model_matrix;
}

const glm::mat4 AffineTransformations::getNormalMatrix() const
{
	return glm::inverseTranspose(m_model_matrix);
}
