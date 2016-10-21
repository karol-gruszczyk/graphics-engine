#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>


using bauasian::Camera;

Camera::~Camera()
{}

void Camera::translate(const glm::vec3& position)
{
	m_view_matrix = glm::translate(m_view_matrix, -position);
	m_position += position;
	updateProjectionViewMatrix();
}

void Camera::setPosition(const glm::vec3& position)
{
	translate(position - m_position);
}

const glm::vec3& Camera::getPosition() const
{
	return m_position;
}

void Camera::rotate(const glm::vec3& rotation)
{
	m_view_matrix = glm::translate(m_view_matrix, m_position);
	m_view_matrix = glm::rotate(m_view_matrix, -m_rotation.y, { 0.f, 1.f, 0.f });
	m_view_matrix = glm::rotate(m_view_matrix, rotation.z, { 0.f, 0.f, 1.f });
	m_view_matrix = glm::rotate(m_view_matrix, -rotation.x, { 1.f, 0.f, 0.f });
	m_view_matrix = glm::rotate(m_view_matrix, m_rotation.y + rotation.y, { 0.f, 1.f, 0.f });
	m_view_matrix = glm::translate(m_view_matrix, -m_position);

	m_rotation += rotation;
	updateForwardVector();
	updateProjectionViewMatrix();
}

void Camera::setRotation(const glm::vec3& rotation)
{
	rotate(rotation - m_rotation);
}

const glm::vec3& Camera::getRotation() const
{
	return m_rotation;
}

void Camera::moveForward(const float& distance)
{
	translate(distance * getForwardVector());
}

void Camera::moveRight(const float& distance)
{
	translate(distance * getRightVector());
}

const glm::vec3& Camera::getForwardVector() const
{
	return m_forward_vector;
}

const glm::vec3& Camera::getRightVector() const
{
	return m_right_vector;
}

const glm::mat4& Camera::getViewMatrix() const
{
	return m_view_matrix;
}

void Camera::setViewMatrix(const glm::mat4& view_matrix)
{
	glm::quat rotation;
	glm::vec3 scale, skew;
	glm::vec4 perspective;
	glm::decompose(view_matrix, scale, rotation, m_position, skew, perspective);
	m_rotation = glm::eulerAngles(rotation) * glm::pi<float>() / 180.f;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
	return m_projection_matrix;
}

const glm::mat4& Camera::getProjectionViewMatrix() const
{
	return m_projection_view_matrix;
}

inline void Camera::updateForwardVector()
{
	m_forward_vector = glm::vec3(glm::cos(m_rotation.x) * glm::sin(m_rotation.y),
	                             glm::sin(m_rotation.x),
	                             -glm::cos(m_rotation.x) * glm::cos(m_rotation.y));
	m_right_vector = glm::vec3(glm::cos(m_rotation.y),
	                           0.f,
	                           glm::sin(m_rotation.y));
}

void Camera::updateProjectionViewMatrix()
{
	m_projection_view_matrix = m_projection_matrix * m_view_matrix;
}
