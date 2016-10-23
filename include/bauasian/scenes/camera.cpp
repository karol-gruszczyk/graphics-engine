#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/rotate_vector.hpp>


using bauasian::Camera;

Camera::~Camera()
{}

const glm::vec3& Camera::getPosition() const
{
	return m_position;
}

void Camera::move(const glm::vec3& position)
{
	setViewMatrix(glm::translate(m_view_matrix, -position));
	m_position += position;
}

void Camera::setPosition(const glm::vec3& position)
{
	move(position - m_position);
}

void Camera::rotate(const float& angle, const glm::vec3& axis)
{
	m_view_matrix = glm::translate(m_view_matrix, m_position);
	m_view_matrix = glm::rotate(m_view_matrix, -angle, axis);
	setViewMatrix(glm::translate(m_view_matrix, -m_position));
}

void Camera::roll(const float& angle)
{
	rotate(angle, m_direction_vector);
	m_up_vector = glm::rotate(m_up_vector, angle, m_direction_vector);
	m_right_vector = glm::cross(m_direction_vector, m_up_vector);
}

void Camera::pitch(const float& angle)
{
	rotate(angle, m_right_vector);
	m_direction_vector = glm::rotate(m_direction_vector, angle, m_right_vector);
	m_up_vector = glm::cross(m_right_vector, m_direction_vector);
}

void Camera::yaw(const float& angle)
{
	rotate(angle, m_up_vector);
	m_direction_vector = glm::rotate(m_direction_vector, angle, m_up_vector);
	m_right_vector = glm::cross(m_direction_vector, m_up_vector);
}

void Camera::lookAt(const glm::vec3& position)
{
	m_direction_vector = glm::normalize(position - m_position);
	m_right_vector = glm::cross(m_direction_vector, m_up_vector);
	setViewMatrix(glm::lookAt(m_position, position, m_up_vector));
}

void Camera::lookAt(const glm::vec3& eye_position, const glm::vec3& position, const glm::vec3& up)
{
	m_position = eye_position;
	m_up_vector = up;
	m_direction_vector = glm::normalize(position - m_position);
	m_right_vector = glm::cross(m_direction_vector, m_up_vector);
	setViewMatrix(glm::lookAt(eye_position, position, up));
}

const glm::vec3& Camera::getDirection() const
{
	return m_direction_vector;
}

const glm::vec3& Camera::getUp() const
{
	return m_up_vector;
}

const glm::vec3& Camera::getRight() const
{
	return m_right_vector;
}

const glm::mat4& Camera::getViewMatrix() const
{
	return m_view_matrix;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
	return m_projection_matrix;
}

const glm::mat4& Camera::getProjectionViewMatrix() const
{
	return m_projection_view_matrix;
}

void Camera::setViewMatrix(const glm::mat4& view_matrix)
{
	m_view_matrix = view_matrix;
	updateProjectionViewMatrix();
}

void Camera::updateProjectionViewMatrix()
{
	m_projection_view_matrix = m_projection_matrix * m_view_matrix;
}
