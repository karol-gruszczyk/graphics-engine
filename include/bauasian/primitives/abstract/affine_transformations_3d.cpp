#include "affine_transformations_3d.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/matrix_decompose.hpp>


using bauasian::AffineTransformations3D;

const glm::vec3& AffineTransformations3D::getPosition() const
{
	return m_position;
}

void AffineTransformations3D::setPosition(const glm::vec3& position)
{
	translate(position - m_position);
}

void AffineTransformations3D::translate(const glm::vec3& position)
{
	m_model_matrix = glm::translate(m_model_matrix, position);
	m_position += position;
}

const glm::vec3& AffineTransformations3D::getRotation() const
{
	return m_rotation;
}

void AffineTransformations3D::setRotation(const glm::vec3& rotation)
{
	rotate(rotation - m_rotation);
}

void AffineTransformations3D::rotate(const glm::vec3& rotation)
{
	m_model_matrix = glm::translate(m_model_matrix, m_pivot);
	m_model_matrix = glm::rotate(m_model_matrix, rotation.y, { 0.f, 1.f, 0.f });
	m_model_matrix = glm::rotate(m_model_matrix, rotation.z, { 0.f, 0.f, 1.f });
	m_model_matrix = glm::rotate(m_model_matrix, rotation.x, { 1.f, 0.f, 0.f });
	m_model_matrix = glm::translate(m_model_matrix, -m_pivot);
	m_rotation += rotation;
}

const glm::vec3& AffineTransformations3D::getScale() const
{
	return m_scale;
}

void AffineTransformations3D::setScale(const glm::vec3& scale)
{
	m_model_matrix = glm::translate(glm::mat4(), m_position);
	m_model_matrix = glm::scale(m_model_matrix, scale);
	m_model_matrix = glm::rotate(m_model_matrix, m_rotation.y, { 0.f, 1.f, 0.f });
	m_model_matrix = glm::rotate(m_model_matrix, m_rotation.z, { 0.f, 0.f, 1.f });
	m_model_matrix = glm::rotate(m_model_matrix, m_rotation.x, { 1.f, 0.f, 0.f });
	m_model_matrix = glm::translate(m_model_matrix, -m_pivot);
	m_scale = scale;
}

const glm::vec3& AffineTransformations3D::getPivot() const
{
	return m_pivot;
}

void AffineTransformations3D::setPivot(const glm::vec3& pivot)
{
	m_model_matrix = glm::translate(m_model_matrix, m_pivot - pivot);
	m_pivot = pivot;
}

const glm::mat4& AffineTransformations3D::getModelMatrix() const
{
	return m_model_matrix;
}

void AffineTransformations3D::setModelMatrix(const glm::mat4& matrix)
{
	m_model_matrix = matrix;
	glm::quat orientation;
	glm::vec3 skew;
	glm::vec4 perpective;
	glm::decompose(matrix, m_scale, orientation, m_position, skew, perpective);
}

const glm::mat4 AffineTransformations3D::getNormalMatrix() const
{
	return glm::inverseTranspose(m_model_matrix);
}

void AffineTransformations3D::addChild(AffineTransformations3D* entity)
{
	m_children.push_back(entity);
}
