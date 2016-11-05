#include "affine_transformations_3d.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>


using bauasian::AffineTransformations3D;

void AffineTransformations3D::setPosition(const glm::vec3& position)
{
	translate(position - m_position);
}

void AffineTransformations3D::translate(const glm::vec3& position)
{
	m_model_matrix = glm::translate(m_model_matrix, position);
	m_position += position;
}

void AffineTransformations3D::setRotation(const glm::vec3& rotation)
{
	rotate(rotation - m_rotation);
}

void AffineTransformations3D::rotate(const glm::vec3& rotation)
{
	m_model_matrix = glm::translate(m_model_matrix, m_pivot);
	m_model_matrix *= glm::mat4_cast(glm::quat(rotation));
	m_model_matrix = glm::translate(m_model_matrix, -m_pivot);
	m_rotation += rotation;
	m_rotation_quat = glm::quat(m_rotation);
}

void AffineTransformations3D::setScale(const glm::vec3& scale)
{
	m_model_matrix = glm::translate(glm::mat4(), m_position);
	m_model_matrix = glm::scale(m_model_matrix, scale);
	m_model_matrix *= glm::mat4_cast(m_rotation_quat);
	m_model_matrix = glm::translate(m_model_matrix, -m_pivot);
	m_scale = scale;
}

void AffineTransformations3D::setPivot(const glm::vec3& pivot)
{
	m_model_matrix = glm::translate(m_model_matrix, m_pivot - pivot);
	m_pivot = pivot;
}

void AffineTransformations3D::setModelMatrix(const glm::mat4& matrix)
{
	m_model_matrix = matrix;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(matrix, m_scale, m_rotation_quat, m_position, skew, perspective);
	m_rotation = glm::eulerAngles(m_rotation_quat) * glm::pi<float>() / 180.f;
}
